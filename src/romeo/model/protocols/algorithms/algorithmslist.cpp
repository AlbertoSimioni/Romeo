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

void AlgorithmsList::addAlgorithm(QString name, QString description, QList<AbstractAlgorithm::AlgorithmParameter> parameters, const QString &dylp, const QString &dyfn)
{
    algorithms::AbstractAlgorithm* alg=new UserDefinedAlgorithm(parameters, name, description, dylp, dyfn);
    algorithms.append(alg);
    emit algorithmsListModified();
}

QList<AbstractAlgorithm*>  AlgorithmsList::getAlgorithmsList(){
    return algorithms;
}

void AlgorithmsList::addAlgorithm(AbstractAlgorithm *alg){
    algorithms.append(alg);
    emit AlgorithmsList::algorithmsListModified();
}


AbstractAlgorithm* AlgorithmsList::getAlgorithm(QString name){

    AbstractAlgorithm* match = 0;
    for(int i =0; i< algorithms.size() && !match;i++){
        if(algorithms[i]->getName()== name)
            match = algorithms[i];
    }

    return match;
}
