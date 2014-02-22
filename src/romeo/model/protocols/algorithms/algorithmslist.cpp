#include "algorithmslist.h"
#include "userdefinedalgorithm.h"
using namespace romeo::model::protocols::algorithms;

AlgorithmsList* AlgorithmsList::instance=0;

AlgorithmsList::AlgorithmsList(QObject *parent) :
    QObject(parent){
}

AlgorithmsList *AlgorithmsList::getInstance(QObject* parent)
{
    if(instance == 0)
    {
        instance=new AlgorithmsList(parent);
    }
    return instance;
}

void AlgorithmsList::addAlgorithm(QString name, QString description, QList<AbstractAlgorithm::AlgorithmParameter> parameters)
{
    algorithms::AbstractAlgorithm* alg=new UserDefinedAlgorithm(parameters, name, description, QString("ss"), QString("aa"));
    algorithms.append(alg);

}
