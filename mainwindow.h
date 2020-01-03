#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <memory>
#include <QMainWindow>
#include <QGraphicsScene>
#include <QThread>
#include <QCloseEvent>
#include<QTimer>
#include "thread/cameraworkthread.h"
#include "src/MMSolver.h"
#include "src/Dlib.h"
#include "thread/udpworkthread.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void closeCameraThread();

    void closeUdpThread();

private:
    Ui::MainWindow *ui;
    QGraphicsScene* scene;
    std::shared_ptr<MMSolver> solverPtr;
    std::shared_ptr<MMSolver> g8mSolverPtr;
    bool center;
    bool started;
    bool hasShape;
    bool first;
    int curIndex;
    std::shared_ptr<ThreadSafeQueue<cv::Mat>> dataQueue;
    std::shared_ptr<ThreadSafeQueue<MatF>> sendQueue;
    std::shared_ptr<cv::VideoCapture> camera;
    CameraWorkThread* workThread;
    UdpWorkThread* sendThread;
    Settings& sets=Settings::instance();
    void closeAll();
    bool KeypointDetectgion(Mat image, MatF &KP);
    std::vector<cv::Point> KeypointDetectgion(Mat image);
    virtual void closeWorkingThread(WorkingThread** t);
private slots:
    void showImage();
    void on_open_clicked();
    // QWidget interface
    void on_settings_triggered();

    void on_start_clicked();

    void on_pause_clicked();

    void on_stop_clicked();

    void on_actionBFM_triggered();

    void on_actionG8M_triggered();

    void on_actionLocal_triggered();

    void on_actionUnity_triggered();
    void setRate(int);
protected:
    void closeEvent(QCloseEvent *event);
};

#endif // MAINWINDOW_H
