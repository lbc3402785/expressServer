#include "test.h"
#include "src/MMSolver.h"
#include "src/Dlib.h"
#include "modelfitting.h"
#include "settings.h"
#include "util/eigenfunctions.h"
#include "obstaclemethodsolver.h"
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
                if(center){
                    KP.col(0).array()-=image.cols/2;
                    KP.col(1).array()-=image.rows/2;
                }
        Eigen::Matrix4Xi colors;
//        FaceModel bfmShape;
//        bfmShape.Initialize("E:\\model\\BFMUV.obj.npz",true);
//        Eigen::Matrix3Xf BFMpoints=bfmShape.Face.transpose();
//        Eigen::Matrix3Xi BFMFaces=bfmShape.TRI.transpose();
//        EigenFunctions<float>::saveEigenPoints(BFMpoints,BFMFaces,colors,"BFMBASE.obj");
//        std::vector<int> BFMkeys;
//        fitting::ModelFitting::loadKeyIndex("E:\\model\\BFM.ini",BFMkeys);
//        FaceModel bfmKeyShape;
//        fitting::ModelFitting::extractBFMKeyModel(bfmShape,BFMkeys,bfmKeyShape);
        //-----------------
        FaceModel shape;
        shape.InitializeG8M(sets.getG8MModel().toStdString(),false);
        Eigen::Matrix3Xf points=shape.Face.transpose();
        MatI QUADRI=shape.QUADRI;

        Eigen::Matrix4Xi polygons=QUADRI.transpose();

        //EigenFunctions<float>::saveEigenPoints(points,polygons,colors,"BASE.obj");
        FaceModel keyShape;
        std::vector<int> g8Mkeys;
        fitting::ModelFitting::loadKeyIndex(sets.getG8MKeyIndexes().toStdString(),g8Mkeys);
        fitting::ModelFitting::extractG8MKeyModel(shape,g8Mkeys,keyShape);
        Eigen::Matrix3Xf keypoints=keyShape.Face.transpose();
        Eigen::Matrix3Xi faces;
        EigenFunctions<float>::saveEigenPoints(keypoints,faces,colors,"key.obj");
        MMSolver g8mSolver;
        g8mSolver.FM=keyShape;
        g8mSolver.FMFull=shape;

        //g8mSolver.params=g8mSolver.SolveProjection(KP,g8mSolver.FM.Face);
        g8mSolver.SX0.resize(g8mSolver.FMFull.SB.cols(),1);
        g8mSolver.SX0.setZero();
        g8mSolver.SX=g8mSolver.SX0;
        g8mSolver.EX=g8mSolver.SX0;
        g8mSolver.FixShape=true;
        g8mSolver.Solve(KP,center);
        std::cout<<"g8mSolver.EX:"<<g8mSolver.EX<<std::endl<<std::flush;
        MatF face=g8mSolver.FMFull.Generate(g8mSolver.SX,g8mSolver.EX);
        points=face.transpose();
        EigenFunctions<float>::saveEigenPoints(points,polygons,colors,"express.obj");

                Mat res = MMSDraw(image, g8mSolver,KP,center);
                imshow("RES", res);
                cv::waitKey();

    }

}
MatD HessionOfObstacleMethod(MatD A,MatD b,MatD x,double range){
    int n=x.rows();
    MatD I=MatD::Identity(n,n);
    return 2*I;
}
MatD JacobiOfObstacleMethod(MatD A,MatD b,MatD x,double range){
    return 2*x;
}
MatD HessionOfObstacleConstrain(MatD A,MatD b,MatD x,double range){
    int n=x.rows();
    MatD H=MatD::Zero(n,n);
    for(int i=0;i<n;i++){
        double xi=x(i,0);
        if(std::abs(xi-range)>1e-8){
            H(i,i)+=1/((range-xi)*(range-xi));
        }else{
            H(i,i)+=1e16;
        }
        if(std::abs(xi+range)>1e-8){
            H(i,i)+=1/((range+xi)*(range+xi));
        }else{
            H(i,i)+=1e16;
        }
    }
    return H;
}
MatD JacobiOfObstacleConstrain(MatD A,MatD b,MatD x,double range){
    int n=x.rows();
    MatD J=MatD::Zero(n,1);
    for(int i=0;i<n;i++){
        double xi=x(i,0);
        double temp=range*range-xi*xi;
        if(std::abs(temp)>1e-8){
            J(i,0)+=(2*xi/temp);
        }else{
            J(i,0)+=(2*xi*1e8);
        }
    }
    return J;
}
double LossOfObstacleMethod(MatD A,MatD b,MatD x,double range){
//    return (x.transpose()*x)(0,0);
    return x.squaredNorm();
}
double LossOfObstacleConstrain(MatD A,MatD b,MatD x,double range){
    int n=x.rows();
    double l21=0;
    double l22=0;
    for(int i=0;i<n;i++){
        double xi=x(i,0);
        if(std::abs(xi-range)>1e-8){
            l21-=std::log(std::abs(xi-range));
        }else{
            l21+=8;
        }

        if(std::abs(xi+range)>1e-8){
            l22-=std::log(std::abs(xi+range));
        }else{
            l22+=8;
        }
    }
    return (l21+l22);
}
void Test::testObstacleMethod()
{
    using namespace std;
    using namespace Eigen;
//    MatF A=MatF::Random(3,3);
//    Eigen::Vector3f x(0.5f,0.4f,0.3f);
//    Eigen::Vector3f b=A*x;
//    cout << "A:" << endl << A << endl;
//    cout << "b:" << endl << b << endl;
//    Eigen::Vector3f x1=SolveObstacleMethod(A,b,1.0f,20,1.01f,1e-8);
//    cout << "x1:" << endl << x1 << endl;
//    cout << "A*x1-b:" << endl << A*x1-b << endl;

    MatD A2=MatD::Random(5,5);
//    MatD x2=MatD::Random(5,1);
    MatD x2(5,1);
    x2<<5.1f,2.001f,-0.98f,-0.99f,-0.102f;
            //x2<<0.999f,2.01f,-1.003f,0.298f,0.335f,0.089f,-1.002f,2.01f,0.0001f,-0.32f;
    MatD b2=A2*x2;
//    cout << "A2:" << endl << A2 << endl;
//    cout << "x2:" << endl << x2 << endl;
//    cout << "b2:" << endl << b2 << endl;
    Eigen::VectorXd x3=SolveObstacleMethod(A2,b2,1.0f,20,1.05f,1e-4);
    cout << "x3:" << endl << x3 << endl;
    cout << "A2*x3-b2:" << endl << (A2*x3-b2).norm() << endl;
    Eigen::VectorXd x4= A2.colPivHouseholderQr().solve(b2);
    cout << "x4:" << endl << x4 << endl;
    cout << "A2*x4-b2:" << endl << (A2*x4-b2).norm() << endl;
//    ObstacleMethodSolver<double,Eigen::RowMajor> solver;
//    solver.LossOfFunction=LossOfObstacleMethod;
//    solver.LossOfConstrain=LossOfObstacleConstrain;
//    solver.HessionOfFunction=HessionOfObstacleMethod;
//    solver.HessionOfConstrain=HessionOfObstacleConstrain;
//    solver.JacobiOfFunction=JacobiOfObstacleMethod;
//    solver.JacobiOfConstrain=JacobiOfObstacleConstrain;
//    MatD x3=solver.solve(A2,b2,1.0);
//    cout << "x3:" << endl << x3 << endl;
//    cout << "A2*x3-b2:" << endl << (A2*x3-b2).norm() << endl;
}
