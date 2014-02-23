#include "abstractprotocol.h"
using namespace romeo::model::protocols;
using namespace romeo::model::protocols::algorithms;
using namespace romeo::model::protocols::features;
AbstractProtocol::AbstractProtocol(QString s, QString d): name(s),description(d)
{
}

AbstractProtocol::AbstractProtocol(QString nomeP, QString desc, AbstractAlgorithm *alg, QList<AbstractFeature *> &feat):
    name(nomeP),description(desc),algorithm(alg),features(feat)
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




