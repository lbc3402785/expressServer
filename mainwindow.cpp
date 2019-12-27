#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <memory>
#include <QFileDialog>
#include <QTextStream>
#include <QCameraInfo>
#include "dialog.h"
#include "settings.h"
#include "drawLandmarks.hpp"
#include "modelfitting.h"
#include "thread/threadsynglobalobj.h"
bool MainWindow::KeypointDetectgion(Mat image, MatF &KP)
{
    vector<vector<Point>> keypoints;
    double S = 0.5;
    Mat simage;
    cv::resize(image, simage, Size(), S, S);

    vector<Rect> rectangles;
    DlibInit(sets.getDlibModel().toStdString());
    DlibFace(simage, rectangles, keypoints);

    if (keypoints.size() <= 0)
    {
        errorcout << "NO POINTS" << endl;
        return false;
    }

    KP = ToEigen(keypoints[0]) * (1.0 / S);

    return true;
}

std::vector<Point> MainWindow::KeypointDetectgion(Mat image)
{
    vector<Point> result;
    vector<vector<Point>> keypoints;
    double S = 0.5;
    Mat simage;
    cv::resize(image, simage, Size(), S, S);

    vector<Rect> rectangles;
    DlibInit(sets.getDlibModel().toStdString());
    DlibFace(simage, rectangles, keypoints);

    if (keypoints.size() <= 0)
    {
        //errorcout << "NO POINTS" << endl;
    }else{
        for(int i=0;i<keypoints[0].size();i++){
            result.emplace_back(keypoints[0][i]*(1/S));
        }
    }
    return result;
}

void MainWindow::closeWorkingThread(WorkingThread **t)
{
    (*t)->setStopSignal(true);
    (*t)->requestInterruption();
    (*t)->quit();
    (*t)->requestInterruption();
    (*t)->wait();
    QThread::msleep(1);
    (*t)->deleteLater();
    (*t)=nullptr;
}
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    scene=new QGraphicsScene(this);
    ui->imageView->setScene(scene);
    hasShape=false;
    started=false;
    curIndex=0;
    first=true;
    workThread=nullptr;
    QList<QCameraInfo> cameras = QCameraInfo::availableCameras();
    int num=cameras.size();
    for(int i=0;i<num;i++){
        ui->id->addItem(QString::number(i),QVariant(i));
    }
    if(num>0){
        ui->textBrowser->append( QString("%1 camera detected!").arg(num));
        ui->id->setCurrentIndex(0);
    }else{
        ui->textBrowser->append("no camera detected!");
    }
    FaceModel BFMModel;
    FaceModel keyBFMModel;
    BFMModel.Initialize(sets.getBFMModel().toStdString(),true);
    std::vector<int> keys;
    fitting::ModelFitting::loadKeyIndex(sets.getBFMKeyIndexes().toStdString(),keys);
    fitting::ModelFitting::extractBFMKeyModel(BFMModel,keys,keyBFMModel);
    MMSolver solver;
    solver.FM=keyBFMModel;
    solver.FMFull=BFMModel;
    solverPtr=std::make_shared<MMSolver>(solver);
    std::cout << "load BFM done!" << std::endl<<std::flush;

    FaceModel shape;
    shape.Initialize(sets.getG8MModel().toStdString(),true);
    FaceModel keyShape;
    std::vector<int> g8Mkeys;
    fitting::ModelFitting::loadKeyIndex(sets.getG8MKeyIndexes().toStdString(),g8Mkeys);
    fitting::ModelFitting::extractG8MKeyModel(shape,g8Mkeys,keyShape);
    MMSolver g8mSolver;
    g8mSolver.FM=keyShape;
    g8mSolver.FMFull=shape;
    g8mSolverPtr=std::make_shared<MMSolver>(g8mSolver);
    std::cout << "load G8M done!" << std::endl<<std::flush;
    sendThread=nullptr;
    workThread=nullptr;
    ui->actionBFM->setChecked(true);
    center=true;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showImage()
{
    cv::Mat image;
    dataQueue->WaitAndPop(image);
    cv::Mat leftTmp;
    std::vector<cv::Point> landMarks = KeypointDetectgion(image);
    int rows=image.rows;
    int cols=image.cols;
    bool success=landMarks.size()>0;
    if(success){
        //std::cout << landMarks.size() << std::endl<<std::flush;
        drawLandmarks(image,landMarks);
        if(sendQueue&&sendThread&&sendThread->getState()==WorkingThread::WorkingState::RUNNING){
            MatF KP=ToEigen(landMarks);//Nx2
            if(center){
                KP.col(0).array()-=sets.getWidth()/2;
                KP.col(1).array()-=sets.getHeight()/2;
            }
            sendQueue->TryPush(KP);
        }
    }
    cv::cvtColor(image,leftTmp,CV_BGR2RGB);
    QImage leftImage=QImage((const uchar*)(leftTmp.data),leftTmp.cols,leftTmp.rows,QImage::Format_RGB888);
    QPixmap leftPix=QPixmap::fromImage(leftImage);
    scene->clear();
    scene->addPixmap(leftPix);
}

void MainWindow::on_open_clicked()
{
    int index=ui->id->currentIndex();
    if(index==-1)return;
    ui->open->setDisabled(true);
    if(ui->open->text()=="open"){
        if(workThread)return;
        cv::VideoCapture capture;
        capture.open(index);
        if(!capture.isOpened()){
            ui->textBrowser->append( QString("open camera index:%1 fail!").arg(index));
            return;
        }else{
            ui->textBrowser->append( QString("open camera index:%1 successful!").arg(index));
        }
        capture.set(cv::CAP_PROP_FRAME_WIDTH, sets.getWidth()*2);
        capture.set(cv::CAP_PROP_FRAME_HEIGHT, sets.getHeight());
        camera=std::make_shared<cv::VideoCapture>(capture);
        dataQueue=std::shared_ptr<ThreadSafeQueue<cv::Mat>>(new ThreadSafeQueue<cv::Mat>());
        workThread=new CameraWorkThread(dataQueue,camera);
        connect(workThread,&CameraWorkThread::returnData,this,&MainWindow::showImage);
        workThread->start();
        ui->open->setText("close");
        ui->id->setDisabled(true);
    }else{
        closeCameraThread();
        ui->open->setText("open");
    }
    ui->open->setDisabled(false);
}
void MainWindow::closeCameraThread()
{
    if(workThread){
        std::lock_guard<std::mutex> lock(sets.obj.cameraTheadMutex);
        closeWorkingThread((WorkingThread **)&workThread);
        camera->release();
        camera.reset();
    }
    scene->clear();
    ui->id->setDisabled(false);
    scene->clear();
}

void MainWindow::closeUdpThread()
{
    if(sendThread){
        std::lock_guard<std::mutex> lock(sets.obj.udpTheadMutex);
        closeWorkingThread((WorkingThread **)&sendThread);
    }
}

void MainWindow::closeAll()
{
    closeCameraThread();
    closeUdpThread();
}
void MainWindow::closeEvent(QCloseEvent *event)
{
    closeAll();
    event->accept();  //接受退出信号，程序退出
}

void MainWindow::on_settings_triggered()
{
    Dialog dialog;
    dialog.exec();
}

void MainWindow::on_start_clicked()
{
    if(sendThread)return;
    ui->start->setFocus();
    ui->start->setDisabled(true);
    sendQueue=std::shared_ptr<ThreadSafeQueue<MatF>>(new ThreadSafeQueue<MatF>());
    sendThread=new UdpWorkThread(solverPtr,g8mSolverPtr,sendQueue);
    if(ui->actionBFM->isChecked()){
        sendThread->setSendMode(UdpWorkThread::SendMode::BFM);
    }else{
        sendThread->setSendMode(UdpWorkThread::SendMode::G8M);
    }
    sendThread->setCenter(center);
    sendThread->start();
    ui->textBrowser->append( QString("start an sendThread!"));
    ui->horizontalSlider->setValue(sendThread->getLambda());
    connect(ui->horizontalSlider,SIGNAL(valueChanged(int)),sendThread,SLOT(setLambda(int)));
}

void MainWindow::on_pause_clicked()
{
    if(sendThread){
        ui->pause->setFocus();
        ui->pause->setDisabled(true);
        if(!sendThread->getPause()&&sendThread->getState()==WorkingThread::WorkingState::RUNNING){
            ui->pause->setText("resume");
            sendThread->setPause(true);
            ui->textBrowser->append( QString("pause the sendThread!"));
        }else if(sendThread->getState()==WorkingThread::WorkingState::PAUSED){
            ui->pause->setText("pause");
            sendThread->setPause(false);
            ui->textBrowser->append( QString("resume the sendThread!"));
        }
        ui->pause->setDisabled(false);
    }

}

void MainWindow::on_stop_clicked()
{
    if(sendThread){
        ui->stop->setDisabled(true);
        ui->stop->setFocus();
        closeUdpThread();
        ui->textBrowser->append( QString("stop the sendThread!"));
        ui->start->setDisabled(false);
        ui->stop->setDisabled(false);
    }
}

void MainWindow::on_actionBFM_triggered()
{
    ui->actionBFM->setChecked(true);
    ui->actionG8M->setChecked(false);
    if(sendThread){
        sendThread->setSendMode(UdpWorkThread::SendMode::BFM);
    }
}

void MainWindow::on_actionG8M_triggered()
{
    ui->actionBFM->setChecked(false);
    ui->actionG8M->setChecked(true);
    if(sendThread){
        sendThread->setSendMode(UdpWorkThread::SendMode::G8M);
    }
}
