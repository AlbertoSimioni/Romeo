/**
* \file protocolslist.cpp
* \author Matteo Pozza
* \date 2014-02-17
**
* \brief Header della classe ProtocolsList del package romeo::model::protocols
*/

#include "protocolslist.h"
#include "staticprotocol.h"
#include "dynamicprotocol.h"
#include "algorithms/userdefinedalgorithm.h"

using namespace romeo::model::protocols;
using namespace romeo::model::protocols::algorithms;

ProtocolsList* ProtocolsList::instance=0;
ProtocolsList::ProtocolsList(QObject *parent) :
    QObject(parent)
{
}

ProtocolsList::~ProtocolsList()
{
    for( int i=0; i<protocolsList.length(); ++i){
        if(protocolsList.at(i))
            delete protocolsList.at(i);
    }
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


AbstractProtocol* ProtocolsList::getProtocol(QString name){
    AbstractProtocol* prot = 0;
    for(int i = 0; i < protocolsList.size() && !prot; i++ ){
        if(protocolsList[i]->getName() == name) prot = protocolsList[i];
    }
    return prot;
}

void ProtocolsList::addProtocol(QString nomeP, QString desc, AbstractAlgorithm *alg, int clusterNum, QList<QString> algParameters, QList<features::AbstractFeature *> feat,bool test,ProtocolType type, int window, int distanceGLCM){

    //controllo che non ci siano altri protocolli nella lista con lo stesso nome
    bool ok=false;
    for(int i=0; i<protocolsList.length() && !ok; ++i)
    {
        if( protocolsList[i]->getName() == nomeP){
            ok=true;
            return;
        }
    }
    switch(type){
    case STATIC : protocolsList.append(new StaticProtocol(nomeP,desc,alg,clusterNum,algParameters,feat,test,window,distanceGLCM));
        break;
    case DYNAMIC: protocolsList.append(new DynamicProtocol(nomeP,desc,alg,clusterNum,algParameters,feat,test));
        break;
    }
    emit ProtocolsList::protocolsListModified();
}

void ProtocolsList::removeProtocol(QString protocolName){
    bool protocolFind = false;
    for(int i = 0; i < protocolsList.size() && !protocolFind; i++ ){
        if(protocolsList[i]->getName() == protocolName){
            protocolFind = true;
            delete protocolsList.takeAt(i);
        }
    }
    emit protocolsListModified();
}
