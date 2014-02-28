#include "abstractprotocol.h"
using namespace romeo::model::protocols;
using namespace romeo::model::protocols::algorithms;
using namespace romeo::model::protocols::features;


AbstractProtocol::AbstractProtocol(QString nomeP, QString desc, AbstractAlgorithm *alg, QList<AbstractFeature *> &feat,bool testProtocol):
    name(nomeP),description(desc),algorithm(alg),features(feat),test(testProtocol)
{

}
QString AbstractProtocol::getName() const
{
    return name;
}

QString AbstractProtocol::getDescription() const
{
    return description;
}


bool AbstractProtocol::getTest() const
{
    return test;
}

QString AbstractProtocol::getAlgorithmName() const
{
    return algorithm->getName();
}




