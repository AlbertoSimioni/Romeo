#include "dynamicprotocol.h"
using namespace romeo::model::protocols;

DynamicProtocol::DynamicProtocol(QString nomeP, QString desc, algorithms::AbstractAlgorithm* alg, QList<features::AbstractFeature*> feat):
    AbstractProtocol(nomeP,desc,alg,feat)
{

}


void DynamicProtocol::execute(romeo::model::datasets::AbstractSubject *subject)
{
 return;
}

ProtocolType DynamicProtocol::getType(){
    return DYNAMIC;
}
