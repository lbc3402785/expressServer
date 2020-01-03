#ifndef OBSTACLEMETHODSOLVER_H
#define OBSTACLEMETHODSOLVER_H
#include <Eigen/Dense>
#include <Eigen/Sparse>
#include <iostream>
#include <tuple>
using namespace Eigen;
using namespace std;
template<typename T,int _Options=Eigen::RowMajor>
class ObstacleMethodSolver
{
public:
    typedef Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic, _Options> MatrixXXT;
    typedef Eigen::Matrix<T, Eigen::Dynamic, 1, _Options> ColXT;
    typedef Eigen::Matrix<T, 1,Eigen::Dynamic, _Options> RowXT;
    ObstacleMethodSolver(){mu=(T)10.0;}
    MatrixXXT solve(MatrixXXT A,MatrixXXT b,T range,T t0=10.0, T epison=1e-6);
    MatrixXXT (*HessionOfFunction)(MatrixXXT A,MatrixXXT b,MatrixXXT x,T range);
    MatrixXXT (*JacobiOfFunction)(MatrixXXT A,MatrixXXT b,MatrixXXT x,T range);
    MatrixXXT (*HessionOfConstrain)(MatrixXXT A,MatrixXXT b,MatrixXXT x,T range);
    MatrixXXT (*JacobiOfConstrain)(MatrixXXT A,MatrixXXT b,MatrixXXT x,T range);
    T (*LossOfFunction)(MatrixXXT A,MatrixXXT b,MatrixXXT x,T range);
    T (*LossOfConstrain)(MatrixXXT A,MatrixXXT b,MatrixXXT x,T range);
private:
    MatrixXXT SolveNewTon(MatrixXXT A,MatrixXXT b,MatrixXXT x0,T range,T t0, T epison);
    T BacktrackingStraightSearch(MatrixXXT A,MatrixXXT b,MatrixXXT x,T range,T t,MatrixXXT deta_x,MatrixXXT g,T alpha=0.49,T beta=0.98);

    T mu;
};

#endif // OBSTACLEMETHODSOLVER_H

template<typename T, int _Options>
typename ObstacleMethodSolver<T,_Options>::MatrixXXT ObstacleMethodSolver<T,_Options>::solve(ObstacleMethodSolver::MatrixXXT A, ObstacleMethodSolver::MatrixXXT b, T range, T t0,T epison)
{
    int n=A.cols();
    MatrixXXT x0(n,1);
    x0.setOnes();
    x0*=0.1f;
    MatrixXXT x=x0;
    T t=t0;
    int m=A.cols();
    while(true){
        MatrixXXT x_star=SolveNewTon(A,b,x,range,t,epison);
        x=x_star;
        cout << "m/t:" << endl << m/t << endl;
        if(m/t<epison)break;
        t*=mu;
    }
    return x;
}

template<typename T, int _Options>
typename ObstacleMethodSolver<T,_Options>::MatrixXXT ObstacleMethodSolver<T,_Options>::SolveNewTon(ObstacleMethodSolver::MatrixXXT A, ObstacleMethodSolver::MatrixXXT b,MatrixXXT x0, T range, T t, T epison)
{
//    cout << "SolveNewTon:" << endl ;
    MatrixXXT x=x0;
    int iter=0;
    while(true){
        MatrixXXT H=HessionOfFunction(A,b,x,range)+(1/t)*HessionOfConstrain(A,b,x,range);
//        cout << "H:"<<H << endl ;
        MatrixXXT Hinverse=H.inverse();
        MatrixXXT g=JacobiOfFunction(A,b,x,range)+(1/t)*JacobiOfConstrain(A,b,x,range);
//        cout << "g:"<<g<< endl ;
        //MatrixXXT deta_x=-Hinverse*g;
//        MatrixXXT S=A*Hinverse*A.transpose();
//        MatrixXXT deta=-Hinverse*g;
//        //cout << "deta:"<<deta<< endl ;
//        MatrixXXT B=A*deta;
//        MatrixXXT vnt=S.colPivHouseholderQr().solve(B);
//        MatrixXXT deta_x=deta-Hinverse*A.transpose()*vnt;
        //cout << "deta_x:"<<deta_x<< endl ;
        MatrixXXT deta_x=A.colPivHouseholderQr().solve(b-A*x);
        if(deta_x.norm()<1e-7)break;
        MatrixXXT result=g.transpose()*Hinverse*g;
        T err2=result(0,0);
        cout << "err2:"<<err2 << endl ;
        if(err2/2<epison)break;
        T step=BacktrackingStraightSearch(A,b,x,range,t,deta_x,g);
        //step=ensureX(x,deta_x,lambda,step);
        x+=step*deta_x;
        iter++;
        cout<<iter << "x:" << endl ;
    }
    return x;
}

template<typename T, int _Options>
T ObstacleMethodSolver<T,_Options>::BacktrackingStraightSearch(ObstacleMethodSolver::MatrixXXT A, ObstacleMethodSolver::MatrixXXT b, ObstacleMethodSolver::MatrixXXT x,T range,T t, ObstacleMethodSolver::MatrixXXT deta_x, ObstacleMethodSolver::MatrixXXT g, T alpha, T beta)
{
    T step=1.0;
    T loss=LossOfFunction(A,b,x,range)+(1/t)*LossOfConstrain(A,b,x,range);
    int iter=0;
    while(true){
        T loss2=(g.transpose()*deta_x)(0,0)*alpha*step;
        MatrixXXT x_deta_x=x+step*deta_x;
        T loss_t_deta_x=LossOfFunction(A,b,x_deta_x,range)+(1/t)*LossOfConstrain(A,b,x_deta_x,range);
        if(std::fabs(loss_t_deta_x-(loss+loss2))>1e-7){
            step*=beta;
            iter++;
        }else{
            break;
        }

//        cout << "loss2:"<<loss2 << endl ;
//        cout << "loss_t_deta_x:"<<loss_t_deta_x << endl ;
//        cout << "loss:"<<loss << endl ;
    }
    cout << "step:"<<step << endl ;
    return step;
}
