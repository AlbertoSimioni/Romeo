#include "staticprotocol.h"
#include <QMessageBox>
#include <QDebug>
#include <QThread>
using namespace romeo::model::protocols;

StaticProtocol::StaticProtocol(QString nomeP, QString desc, algorithms::AbstractAlgorithm* alg, int clusterNum, QList<QString> algParameters, QList<features::AbstractFeature*> feat, bool testProtocol, int window, int distance):
    AbstractProtocol(nomeP,desc,alg, clusterNum, algParameters, feat,testProtocol), windowSize(window), distanceToGLCM(distance)
{

}


void StaticProtocol::execute(romeo::model::datasets::AbstractSubject *subject)
{
    //if(subject->getType() == "2D"){fun<2>();}
    //else{fun<3>();}


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

