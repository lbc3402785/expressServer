#include "modelfitting.h"
#include <QSettings>
#include "settings.h"
namespace  fitting{
float shapeFactor=2.2f;
float weight=5.0f;
float Lambdas[7] = { 100.0, 30.0, 10.0, 5.0,4.0,3.0,2.0};
const double pi = std::acos(-1);
float eps=std::cos(pi/4);
ModelFitting::ModelFitting()
{

}
void ModelFitting::loadKeyIndex(std::string keyPath,std::vector<int>& keys){
    QSettings settings(QString::fromStdString(keyPath),QSettings::IniFormat);
    keys.clear();
    for(int i=1;i<=68;i++){
        QString key=QString::number(i);
        int value=settings.value(key,-1).value<int>();
        if(value==-1){
            std::cerr<<"invalid index!"<<std::endl<<std::flush;
        }else{
            //std::cerr<<"value:"<<value<<std::endl<<std::flush;
            keys.push_back(value-1);
        }
    }

}
void ModelFitting::extractBFMKeyModel(const FaceModel &BFMModel, std::vector<int> &indexes, FaceModel &keyModel)
{
    extractKeyShape(BFMModel.SB,indexes,keyModel.SB);
    extractKeyShape(BFMModel.EB,indexes,keyModel.EB);
    extractKeyFace(BFMModel.Face,indexes,keyModel.Face);
}

void ModelFitting::extractG8MKeyModel(const FaceModel &BFMModel, std::vector<int> &indexes, FaceModel &keyModel)
{
    extractKeyShape(BFMModel.EB,indexes,keyModel.EB);
    extractKeyFace(BFMModel.Face,indexes,keyModel.Face);
    keyModel.SB=keyModel.EB;
}

void ModelFitting::extractKeyShape(const MatF &SB, std::vector<int> &indexes, MatF &keySB)
{
    int n=indexes.size();
    int L=SB.cols();
    keySB.resize(n*3,L);
    for(int i=0;i<n;i++){
        int index=indexes[i];
        keySB.block(i*3,0,3,L)=SB.block(index*3,0,3,L);
    }
}

void ModelFitting::extractKeyFace(const MatF Face, std::vector<int> &indexes, MatF &keyFace)
{
    keyFace.resize(indexes.size(),3);
    for(int i=0;i<keyFace.rows();i++){
        keyFace.row(i)=Face.row(indexes[i]);
    }
}



float ModelFitting::computeAvgDis(Matrix3Xf &srcKeyPoints, Matrix3Xf &dstKeyPoints)
{
    int num=srcKeyPoints.cols();
    float sum=0.0f;
    for(int i=0;i<num;i++){
        Eigen::Vector3f diff=srcKeyPoints.col(i)-dstKeyPoints.col(i);
        sum+=diff.norm();
        std::cout<<i<<" "<<diff.norm()<<std::endl;
    }
    return sum/num;
}

float ModelFitting::computeScaleOfSrc2Dst(Eigen::Matrix3Xf &src, Eigen::Matrix3Xf &dst)
{
    if(src.cols()!=68||src.cols()!=dst.cols()){
        std::cout<<"points number is not matched!"<<std::endl<<std::flush;
    }
    std::vector<float> candidates;
    for(int i=0;i<8;i++){
        Eigen::Vector3f srcLine=src.col(16-i)-src.col(i);
        Eigen::Vector3f dstLine=dst.col(16-i)-dst.col(i);
        candidates.push_back(dstLine.norm()/srcLine.norm());
    }
    std::sort(candidates.begin(), candidates.end());
    return (candidates[3]+candidates[4])/2;
}
void loadKeyIndex(std::string keyPath,std::vector<int>& keys){
    QSettings settings(QString::fromStdString(keyPath),QSettings::IniFormat);
    keys.clear();
    for(int i=1;i<=68;i++){
        QString key=QString::number(i);
        int value=settings.value(key,-1).value<int>();
        if(value==-1){
            std::cerr<<"invalid index!"<<std::endl<<std::flush;
        }else{
            //std::cerr<<"value:"<<value<<std::endl<<std::flush;
            keys.push_back(value-1);
        }
    }

}


void ModelFitting::extractKeyPoints(const Matrix3Xf &points, std::vector<int> &indexes, Matrix3Xf &out)
{
    out.resize(3,indexes.size());
    for(int i=0;i<out.cols();i++){
        out.col(i)=points.col(indexes[i]);
    }
}

/**
 * @brief ModelFitting::computeShapeX
 * @param srcKeyPoints
 * @param dstKeyPoints
 * @param keySB         n*3x199
 * @param shapeX
 * @param lambda
 * keySB*shapeX=SBX n*3x199 199X1=n*3x1
 */
void ModelFitting::computeShapeX(Eigen::Matrix3Xf& srcKeyPoints,Eigen::Matrix3Xf&dstKeyPoints,MatF& keySB,MatF& shapeX,float lambda)
{
    Eigen::Matrix3Xf diff=srcKeyPoints-dstKeyPoints;//3xn
    MatF error=diff.transpose();//nx3;
    error=Reshape(error,1);//n*3x1
    shapeX=SolveLinear(keySB,error,lambda);
}

void ModelFitting::filterRepeat(std::map<int, int> &pointsMap, const std::map<int, int> &keyMap)
{
    std::map<int,bool> toDel;
    for( std::map<int,int>::const_iterator it = pointsMap.begin(); it != pointsMap.end();  it++){
        int key = it->first;
        if(!keyMap.count(key)>0){
            int value = it->second;
            for( std::map<int,int>::const_iterator kit = keyMap.begin(); kit != keyMap.end(); kit++ ){
                if(value==kit->second){
                    toDel[key]=true;
                }
            }
        }
    }
    for( std::map<int,int>::const_iterator it = pointsMap.begin(); it != pointsMap.end();){
        int key = it->first;
        if(toDel.count(key)>0){
            pointsMap.erase(it++);
        }else{
            it++;
        }
    }
}

void ModelFitting::extractIndexes(std::map<int, int> &pointsMap, std::vector<int> &keys, std::vector<int> &values)
{
    for( std::map<int,int>::const_iterator it = pointsMap.begin(); it != pointsMap.end();  it++){
        int key = it->first;
        int value = it->second;
        keys.push_back(key);
        values.push_back(value);
    }
}

std::map<int,int> ModelFitting::makeKeymap(std::vector<int> srcIndexes, std::vector<int> dstIndexes)
{
    std::map<int,int> keyMap;
    for(int i=0;i<srcIndexes.size();i++){
        keyMap[srcIndexes[i]]=dstIndexes[i];
    }
    return keyMap;
}

void ModelFitting::subKey(const std::map<int,int>& keyMap, std::vector<int> &ids)
{
    auto iter = ids.begin();
    while (iter !=ids.end()) {
        if (keyMap.count(*iter)>0) {
            iter = ids.erase(iter);
        }
        else {
            ++iter;
        }
    }
}

void ModelFitting::fittingShape(const MatF&KP,MMSolver& solver,bool center)
{
    solver.Solve(KP,center);
}

float ModelFitting::fittingExpression(const MatF &KP, MMSolver &solver,bool center)
{
//    MatF Face=solver.FM.Face;
//    MatF S = solver.FM.Face * 0;
//    MatF E = solver.FM.Face * 0;
//    for(int i=0;i<4;i++){

//            solver.params = solver.SolveProjection(KP, Face);
//        MatF FaceS = solver.FM.SB * solver.SX;
//        S = Reshape(FaceS, 3);
//        solver.EX = solver.SolveShape(solver.params, KP, solver.FM.Face + S, solver.FM.EB, Lambdas[2] * 1,center);
//        MatF FaceE = solver.FM.EB * solver.EX;
//        E = Reshape(FaceE, 3);
//        Face = solver.FM.Face + S + E;
//    }
    solver.FixShape=true;
    solver.SX0=solver.SX;
    float error=solver.Solve(KP,center);
    solver.FixShape=false;
    return error;
}


void saveSelectObj(std::map<int,int> pointsMap,std::map<int,int> keyMap,Eigen::Matrix3Xf srcPoints,std::string name){
    std::ofstream out(name);
    for( std::map<int,int>::const_iterator it = pointsMap.begin(); it != pointsMap.end(); ++it )
    {
        int key = it->first;
        Eigen::Vector3f p=srcPoints.col(key);
        out<<"v "<<p(0)<<" "<<p(1)<<" "<<p(2)<<" ";
        if(keyMap.count(key)>0){
            out<<255<<" "<<0<<" "<<0<<" "<<255<<std::endl;
        }else{
            out<<0<<" "<<255<<" "<<0<<" "<<255<<std::endl;
        }
    }
}

}//namespace end
