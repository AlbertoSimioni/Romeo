#include "dynamicprotocol.h"
#include <QMessageBox>
#include <QDebug>
#include <QThread>
using namespace romeo::model::protocols;

DynamicProtocol::DynamicProtocol(QString nomeP, QString desc, algorithms::AbstractAlgorithm* alg, int clusterNum, QList<QString> algParameters, QList<features::AbstractFeature*> feat, bool testProtocol):
    AbstractProtocol(nomeP,desc,alg, clusterNum, algParameters, feat,testProtocol)
{

}


void DynamicProtocol::execute(romeo::model::datasets::AbstractSubject *subject,QString path,bool saveFeatures,QString outputFormat)
{



}

ProtocolType DynamicProtocol::getType(){
    return DYNAMIC;
}

int DynamicProtocol::getWindowSize() const
{
    return 0;
}

int DynamicProtocol::getDistanceToGlcm() const
{
    return 0;
}
