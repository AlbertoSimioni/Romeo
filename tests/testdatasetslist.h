#ifndef TESTDATASETSLIST_H
#define TESTDATASETSLIST_H

#include <QtTest>
#define private public
#include <../src/romeo/model/datasets/datasetslist.h>
#include <../src/romeo/model/datasets/dataset2d.h>


using namespace romeo::model::datasets;
#ifndef INPUTFORMAT
#define INPUTFORMAT
Q_DECLARE_METATYPE(romeo::model::InputFormat)
#endif

class TestDatasetsList : public QObject
{
    Q_OBJECT

public:
    explicit TestDatasetsList(QObject *parent = 0);

private slots:
    void getInstance();
    void getDataset();
    void addDataset();
    void getDatasetsList();
    void getDatasetsNames();
    void addDatasetFile();
    void getNextDataset();
    void deleteDataset();
    void deleteProtocolAssociations();

};


#endif // TESTDATASETSLIST_H
