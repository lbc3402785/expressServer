#include "test.h"
#include "src/MMSolver.h"
#include "src/Dlib.h"
#include "modelfitting.h"
#include "settings.h"
#include "util/eigenfunctions.h"
Test::Test()
{

}
Settings& sets=Settings::instance();
bool KeypointDetectgion(Mat image, MatF &KP)
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
void Test::testG8M(std::string picPath)
{

    cv::Mat image= imread(picPath);
    MatF KP;
    bool center=false;
    if(KeypointDetectgion(image, KP)){
//        if(center){
//            KP.col(0).array()-=image.cols/2;
//            KP.col(1).array()-=image.rows/2;
//        }
        FaceModel shape;
        shape.Initialize(sets.getG8MModel().toStdString(),true);
        FaceModel keyShape;
        std::vector<int> g8Mkeys;
        fitting::ModelFitting::loadKeyIndex(sets.getG8MKeyIndexes().toStdString(),g8Mkeys);
        fitting::ModelFitting::extractG8MKeyModel(shape,g8Mkeys,keyShape);
        MMSolver g8mSolver;
        g8mSolver.FM=keyShape;
        g8mSolver.FMFull=shape;
        g8mSolver.Solve(KP);
        g8mSolver.EX*=0;
        std::cout<<"g8mSolver.EX:"<<g8mSolver.EX<<std::endl<<std::flush;
        MatF face=g8mSolver.FMFull.Generate(g8mSolver.SX,g8mSolver.EX);
        Eigen::Matrix3Xf points=face.transpose();
        Eigen::Matrix4Xi colors;
        MatI QUADRI=shape.QUADRI;

        Eigen::Matrix4Xi polygons=QUADRI.transpose();
        EigenFunctions<float>::saveEigenPoints(points,polygons,colors,"test.obj");
        Mat res = MMSDraw(image, g8mSolver,KP);
        imshow("RES", res);

    }

}
