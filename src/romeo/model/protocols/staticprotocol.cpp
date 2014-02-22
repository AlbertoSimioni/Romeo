#include "staticprotocol.h"
using namespace romeo::model::protocols;


StaticProtocol::StaticProtocol(QString nomeP, QString desc, algorithms::AbstractAlgorithm *alg, QList<features::AbstractFeature *> feat): AbstractProtocol(nomeP,desc)
{

}

void StaticProtocol::execute(romeo::model::datasets::AbstractSubject *subject)
{
 return;
}
