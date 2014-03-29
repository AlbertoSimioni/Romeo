#ifndef TESTABSTRACTDATASET_H
#define TESTABSTRACTDATASET_H

#include <QtTest>
#define private public
#include <../src/romeo/controller/controller.h>
#include <../src/romeo/model/protocols/features/featureslist.h>
#include <../src/romeo/model/datasets/dataset2d.h>
#include <../src/romeo/model/datasets/dataset2dt.h>
#include <../src/romeo/model/datasets/abstractdataset.h>
#include <../src/romeo/model/protocols/dynamicprotocol.h>
#include <../src/romeo/model/protocols/staticprotocol.h>
#include <../src/romeo/model/protocols/algorithms/kmeans.h>
#include <../src/romeo/model/protocols/algorithms/hierarchical.h>
#include <../src/romeo/model/protocols/algorithms/fuzzycmeans.h>
#include <../src/romeo/model/protocols/features/abstractfeature.h>
#include <../src/romeo/model/protocols/features/firstorderfeature.h>

using namespace romeo::controller;
using namespace romeo::model::datasets;
using namespace romeo::model::protocols;
using namespace romeo::model::protocols::algorithms;

class TestAbstractDataset : public QObject
{
    Q_OBJECT

public:
    explicit TestAbstractDataset(QObject *parent = 0);

private slots:
    void createNewSubject();
//   void associateProtocol();
    void getName();
    void setName();
    void getProtocolResults();
  /*   void getSubjectList();
    void removeProtocolAssociation();
    void getAssociatedProtocolsList();
    void getTypeString();
    void addResult();
    void getResultsList();
    void getResultPath();
    void getProtocol();
    void getProtocolList();
    void getSubject();
    void deleteSubject();*/
    void executeAnalysis();

};


#endif // TESTABSTRACTDATASET_H
