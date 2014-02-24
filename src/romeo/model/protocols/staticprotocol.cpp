#include "staticprotocol.h"
using namespace romeo::model::protocols;

StaticProtocol::StaticProtocol(QString nomeP, QString desc, algorithms::AbstractAlgorithm* alg, QList<features::AbstractFeature*> feat, int window, int distance):
    AbstractProtocol(nomeP,desc,alg,feat), windowSize(window), distanceToGLCM(distance)
{

}


void StaticProtocol::execute(romeo::model::datasets::AbstractSubject *subject)
{
 return;
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

int StaticProtocol::getDistanceToGLCM() const
{
    return distanceToGLCM;
}

void StaticProtocol::setDistanceToGLCM(int value)
{
    distanceToGLCM = value;
}

