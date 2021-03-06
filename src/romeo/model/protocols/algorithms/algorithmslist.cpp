/**
* \file algorithmslist.cpp
* \author Alberto Cavallarin
* \date 17-02-2014
**
* \brief  Header della classe AlgorithmsList del package romeo::model::protocols::features
*/

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

AlgorithmsList::~AlgorithmsList()
{
    for (int i=0; i<algorithms.length(); ++i)
    {
        if(algorithms.at(i))
            delete algorithms.at(i);
    }
}

void AlgorithmsList::addAlgorithm(QString name, QString description, QList<AbstractAlgorithm::AlgorithmParameter> parameters,QString dylp,QString dyfn)
{
    if (!this->getAlgorithm(name)){
    algorithms::AbstractAlgorithm* alg=new UserDefinedAlgorithm(parameters, name, description, dylp, dyfn);
    algorithms.append(alg);
    emit algorithmsListModified();
    }
}

QList<AbstractAlgorithm*>  AlgorithmsList::getAlgorithmsList(){
    return algorithms;
}

void AlgorithmsList::addAlgorithm(AbstractAlgorithm *alg){
    if (!this->getAlgorithm(alg->getName())){
    algorithms.append(alg);
    emit algorithmsListModified();
    }
}


AbstractAlgorithm* AlgorithmsList::getAlgorithm(QString name){

    AbstractAlgorithm* match = 0;
    for(int i =0; i< algorithms.size() && !match;i++){
        if(algorithms[i]->getName() == name)
            match = algorithms[i];
    }
    return match;
}
