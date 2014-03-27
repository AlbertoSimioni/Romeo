#ifndef TESTDATASETSCONTROLLER_H
#define TESTDATASETSCONTROLLER_H

#include <QtTest>
#define private public
#include <../src/romeo/controller/controller.h>
#include <../src/romeo/model/datasets/datasetslist.h>
#include <../src/romeo/model/datasets/dataset2d.h>
#include <../src/romeo/model/datasets/dataset2dt.h>
#include <../src/romeo/model/datasets/dataset3d.h>
#include <../src/romeo/model/datasets/dataset3dt.h>

using namespace romeo::controller;
using namespace romeo::model::datasets;

class TestDatasetsController : public QObject
{
    Q_OBJECT

public:
    explicit TestDatasetsController(QObject *parent = 0);

private slots:
    void getInstance();
    void checkDatasetName();
    void checkSubjectName();
    void addDataset();
    void addSubject();
    void deleteSubject();
    void deleteCurrentDataset();
    void getMainWindow();
};


#endif // TESTDATASETSCONTROLLER_H
