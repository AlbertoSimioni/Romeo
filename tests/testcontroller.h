#ifndef TESTCONTROLLER_H
#define TESTCONTROLLER_H

#include <QtTest>
#define private public
#include <../src/romeo/controller/controller.h>
#include <../src/romeo/model/core/modelcore.h>
#include <../src/romeo/model/datasets/datasetslist.h>
#include <../src/romeo/model/datasets/dataset2d.h>
#include <../src/romeo/model/datasets/dataset2dt.h>
#include <../src/romeo/model/datasets/dataset3d.h>
#include <../src/romeo/model/datasets/dataset3dt.h>
#include <../src/romeo/model/protocols/protocolslist.h>
#include <../src/romeo/model/protocols/staticprotocol.h>
#include <../src/romeo/model/protocols/dynamicprotocol.h>
#include <../src/romeo/model/protocols/algorithms/algorithmslist.h>
#include <../src/romeo/model/protocols/algorithms/userdefinedalgorithm.h>
#include <../src/romeo/model/protocols/features/featureslist.h>
#include <../src/romeo/model/protocols/features/firstorderfeature.h>
#include <../src/romeo/model/protocols/features/secondorderfeature.h>
#include <../src/romeo/model/protocols/features/dynamicfeature.h>

using namespace romeo::controller;
using namespace romeo::model::core;
using namespace romeo::model::datasets;
using namespace romeo::model::protocols;
using namespace romeo::model::protocols::algorithms;

class TestController : public QObject
{
    Q_OBJECT

public:
    explicit TestController(QObject *parent = 0);

private slots:
    void getInstance();
    void checkProtocolName();
    void checkAlgorithmName();
    void checkFeatureName();
    void checkDatasetName();
    //void viewNewProtocolDialog();
    void checkSubjectName();
    void addProtocol();
    void addAlgorithm();
    void addFeature();
    void addDataset();
    void addSubject();
    void deleteSubject();
    void deleteProtocol();
    void deleteCurrentDataset();
    void associateProtocol();
    void removeProtocolAssociation();
};


#endif // TESTCONTROLLER_H
