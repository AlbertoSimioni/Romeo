#ifndef TESTPROTOCOLSCONTROLLER_H
#define TESTPROTOCOLSCONTROLLER_H

#include <QtTest>
#define private public
#include <../src/romeo/controller/controller.h>
#include <../src/romeo/controller/protocolscontroller.h>
#include <../src/romeo/model/protocols/protocolslist.h>
#include <../src/romeo/model/datasets/dataset2d.h>
#include <../src/romeo/model/protocols/staticprotocol.h>
#include <../src/romeo/model/protocols/dynamicprotocol.h>
#include <../src/romeo/model/protocols/algorithms/algorithmslist.h>
#include <../src/romeo/model/protocols/algorithms/userdefinedalgorithm.h>
#include <../src/romeo/model/protocols/features/featureslist.h>
#include <../src/romeo/model/protocols/features/firstorderfeature.h>
#include <../src/romeo/model/protocols/features/secondorderfeature.h>
#include <../src/romeo/model/protocols/features/dynamicfeature.h>

using namespace romeo::controller;
using namespace romeo::model::datasets;
using namespace romeo::model::protocols;
using namespace romeo::model::protocols::algorithms;

class TestProtocolsController : public QObject
{
    Q_OBJECT

public:
    explicit TestProtocolsController(QObject *parent = 0);

private slots:
    void getInstance();
    void checkProtocolName();
    void addProtocol();
    void deleteProtocol();
    void associateProtocol();
    void removeProtocolAssociation();
    void modifyProtocol();
};


#endif // TESTPROTOCOLSCONTROLLER_H
