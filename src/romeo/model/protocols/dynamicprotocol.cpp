#include "dynamicprotocol.h"
using namespace romeo::model::protocols;

DynamicProtocol::DynamicProtocol(QString nomeP, QString desc, algorithms::AbstractAlgorithm* alg, QList<features::AbstractFeature*> feat, bool testProtocol):
    AbstractProtocol(nomeP,desc,alg,feat,testProtocol)
{

}


void DynamicProtocol::execute(romeo::model::datasets::AbstractSubject *subject)
{
 return;
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
