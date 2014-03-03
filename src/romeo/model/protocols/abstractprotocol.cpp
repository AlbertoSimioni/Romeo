#include "abstractprotocol.h"

#include <QStringList>
using namespace romeo::model::protocols;
using namespace romeo::model::protocols::algorithms;
using namespace romeo::model::protocols::features;


AbstractProtocol::AbstractProtocol(QString nomeP, QString desc, AbstractAlgorithm *alg, int clusterNum, QList<QString> algParameters, QList<AbstractFeature *> &feat,bool testProtocol):
    name(nomeP),description(desc),algorithm(alg), nClusters(clusterNum), algorithmParameters(algParameters), features(feat),test(testProtocol)
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

QStringList AbstractProtocol::getFeaturesName() const
{
    QStringList featureNames;
    for(int i=0; i< features.length(); ++i)
    {
        featureNames << features.at(i)->getName();
    }
    return featureNames;
}

QString AbstractProtocol::getAlgorithmName() const
{
    return algorithm->getName();
}
int AbstractProtocol::getNClusters() const
{
    return nClusters;
}

void AbstractProtocol::setNClusters(int value)
{
    nClusters = value;
}
QList<QString> AbstractProtocol::getAlgorithmParameters() const
{
    return algorithmParameters;
}

void AbstractProtocol::setAlgorithmParameters(const QList<QString> &value)
{
    algorithmParameters = value;
}






