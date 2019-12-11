#ifndef MODELFITTING_H
#define MODELFITTING_H
#include <Eigen/Dense>
#include <map>
#include "src/MMSolver.h"
namespace  fitting{
class ModelFitting
{
public:


    ModelFitting();
    static void loadKeyIndex(std::string keyPath,std::vector<int>& keys);
    static void extractKeyModel(const FaceModel &BFMModel,std::vector<int>& indexes,FaceModel& keyModel);
    static void extractKeyShape(const MatF &SB,std::vector<int>& indexes,MatF& keySB);
    static void extractKeyFace(const MatF Face,std::vector<int>& indexes,MatF& keyFace);
    static void extractKeyPoints(const Eigen::Matrix3Xf &points,std::vector<int>& indexes,Eigen::Matrix3Xf& out);
    static float computeAvgDis(Eigen::Matrix3Xf& srcKeyPoints,Eigen::Matrix3Xf&dstKeyPoints);
    static float computeScaleOfSrc2Dst(Eigen::Matrix3Xf& src,Eigen::Matrix3Xf&dst);
    static void computeShapeX(Eigen::Matrix3Xf& srcKeyPoints,Eigen::Matrix3Xf&dstKeyPoints,MatF& keySB,MatF& shapeX,float lambda);

    static void filterRepeat(std::map<int,int>& pointsMap,const std::map<int,int>& keyMap);

    static void extractIndexes(std::map<int,int>& pointsMap, std::vector<int> &keys, std::vector<int> &values);

    static std::map<int,int> makeKeymap(std::vector<int> srcIndexes,std::vector<int> dstIndexes);
    static void subKey(const std::map<int,int>& keyMap,std::vector<int> &ids);
    static void fittingShape(const MatF&KP, MMSolver& solver);
    static void fittingExpression(const MatF&KP, MMSolver& solver);
};
}


#endif // MODELFITTING_H
