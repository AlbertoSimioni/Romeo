#include "protocolslist.h"
using namespace romeo::model::protocols;
ProtocolsList::ProtocolsList(QObject *parent) :
    QObject(parent)
{
}

/*ProtocolsList::~ProtocolsList()
{
    foreach(AbstractProtocol* p , protocolsList){
        delete p;
    }
}*/
