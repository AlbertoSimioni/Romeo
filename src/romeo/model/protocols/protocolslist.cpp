#include "protocolslist.h"
#include "staticprotocol.h"
#include "dynamicprotocol.h"

#include <src/romeo/model/protocols/algorithms/userdefinedalgorithm.h>
using namespace romeo::model::protocols;
using namespace romeo::model::protocols::algorithms;

ProtocolsList* ProtocolsList::instance=0;
ProtocolsList::ProtocolsList(QObject *parent) :
    QObject(parent)
{
    /*QList<algorithms::AbstractAlgorithm::AlgorithmParameter> param;
    algorithms::AbstractAlgorithm::AlgorithmParameter param1(QString("param"), AbstractAlgorithm::BOOL, QString("default"));
    algorithms::AbstractAlgorithm::AlgorithmParameter param2(QString("param"), AbstractAlgorithm::CHAR, QString("default"));
    param.append(param1);
    param.append(param2);
    algorithms::AbstractAlgorithm* alg=new algorithms::UserDefinedAlgorithm(param, QString("nome alg"), QString("desc"), QString("libreria"), QString("nomefunz"));

    QString n=QString("Nome del protocollo");
    QList<features::AbstractFeature*> feat;
    protocolsList.append(new StaticProtocol(n,QString("descrizione"),alg,feat));*/
}

ProtocolsList *ProtocolsList::getInstance(QObject *parent)
{
    if(instance == 0)
    {
        instance= new ProtocolsList(parent);
    }
    return instance;
}

QList<AbstractProtocol *> ProtocolsList::getProtocolsList() const
{
    return protocolsList;
}


void ProtocolsList::addProtocol(QString &name, QString desc, QString &algorithm, QList<QString> &features, ProtocolType type){
    //DA IMPLEMENTARE
}


AbstractProtocol* ProtocolsList::getProtocol(QString name){
    AbstractProtocol* prot = 0;
    for(int i = 0; i < protocolsList.size() && !prot; i++ ){
        if(protocolsList[i]->getName() == name) prot = protocolsList[i];
    }
    return prot;
}

void ProtocolsList::addProtocol(QString nomeP, QString desc, AbstractAlgorithm *alg, QList<features::AbstractFeature *> &feat,ProtocolType type){
    switch(type){
    case STATIC : protocolsList.append(new StaticProtocol(nomeP,desc,alg,feat));
        break;
    case DYNAMIC: protocolsList.append(new DynamicProtocol(nomeP,desc,alg,feat));
        break;
    }
    emit ProtocolsList::protocolsListModified();
}

/*ProtocolsList::~ProtocolsList()
{
    foreach(AbstractProtocol* p , protocolsList){
        delete p;
    }
}*/
