/**
* \file staticprotocol.cpp
* \author Matteo Pozza
* \date 2014-02-07
**
* \brief Header della classe StaticProtocol del package romeo::model::protocols
*/

#include "staticprotocol.h"
#include <QThread>

using namespace romeo::model::protocols;
using namespace romeo::model::imageIO;
using namespace romeo::model;

StaticProtocol::StaticProtocol(QString nomeP, QString desc, algorithms::AbstractAlgorithm* alg, int clusterNum, QList<QString> algParameters, QList<features::AbstractFeature*> feat, bool testProtocol, int window, int distance):
    AbstractProtocol(nomeP,desc,alg, clusterNum, algParameters, feat,testProtocol), windowSize(window), distanceToGLCM(distance)
{
}

void StaticProtocol::execute(romeo::model::datasets::AbstractSubject *subject,QString path,bool saveFeatures,QString outputFormat)
{
    setStopAnalysis(false);
    InputFormat dimensions = subject->getType();
    if(dimensions == TYPE2D)
        templateExecute<2>(subject,path,saveFeatures,outputFormat);
    else
        templateExecute<3>(subject,path,saveFeatures,outputFormat);
}

ProtocolType StaticProtocol::getType(){
    return STATIC;
}
int StaticProtocol::getWindowSize() const
{
    return windowSize;
}

void StaticProtocol::setWindowSize(int value)
{
    windowSize = value;
}

int StaticProtocol::getDistanceToGlcm() const
{
    return distanceToGLCM;
}

void StaticProtocol::setDistanceToGlcm(int value)
{
    distanceToGLCM = value;
}
