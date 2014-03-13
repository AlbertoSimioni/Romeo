/**
* \file dynamicprotocol.cpp
* \author Matteo Pozza
* \date 2014-02-17
**
* \brief Header della classe DynamicProtocol del package romeo::model::protocols
*/

#include "dynamicprotocol.h"
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
    return 3;
}

int DynamicProtocol::getDistanceToGlcm() const
{
    return 1;
}
