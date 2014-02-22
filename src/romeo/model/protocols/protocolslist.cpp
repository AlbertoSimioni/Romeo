#include "protocolslist.h"
#include "staticprotocol.h"

#include <src/romeo/model/protocols/algorithms/userdefinedalgorithm.h>
using namespace romeo::model::protocols;
using namespace romeo::model::protocols::algorithms;

ProtocolsList* ProtocolsList::instance=0;
ProtocolsList::ProtocolsList(QObject *parent) :
    QObject(parent)
{
    QList<algorithms::AbstractAlgorithm::AlgorithmParameter> param;
    algorithms::AbstractAlgorithm::AlgorithmParameter param1(QString("param"), AbstractAlgorithm::BOOL, QString("default"));
    algorithms::AbstractAlgorithm::AlgorithmParameter param2(QString("param"), AbstractAlgorithm::CHAR, QString("default"));
    param.append(param1);
    param.append(param2);
    algorithms::AbstractAlgorithm* alg=new algorithms::UserDefinedAlgorithm(param, QString("nome alg"), QString("desc"), QString("libreria"), QString("nomefunz"));

    QString n=QString("Nome del protocollo");
    QList<features::AbstractFeature*> feat;
    protocolsList.append(new StaticProtocol(n,QString("descrizione"),alg,feat));
}

ProtocolsList *ProtocolsList::getInstance()
{
    if(instance == 0)
    {
        instance= new ProtocolsList();
    }
    return instance;
}
QList<AbstractProtocol *> ProtocolsList::getProtocolsList() const
{
    return protocolsList;
}




/*ProtocolsList::~ProtocolsList()
{
    foreach(AbstractProtocol* p , protocolsList){
        delete p;
    }
}*/
