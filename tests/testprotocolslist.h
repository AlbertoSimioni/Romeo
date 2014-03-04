#ifndef TESTPROTOCOLSLIST_H
#define TESTPROTOCOLSLIST_H

#include <QtTest>
#define private public
#include <../src/romeo/model/protocols/protocolslist.h>
#include <../src/romeo/model/protocols/staticprotocol.h>
#include <../src/romeo/model/protocols/dynamicprotocol.h>
#include <../src/romeo/model/protocols/algorithms/userdefinedalgorithm.h>

using namespace romeo::model::protocols;

class TestProtocolsList : public QObject // _LINE
{
    Q_OBJECT

public:
    explicit TestProtocolsList(QObject *parent = 0);

private slots:
    void getInstance();
    void addRemoveGetProtocol();
};


#endif // TESTPROTOCOLSLIST_H
