#ifndef TESTWRITER_H
#define TESTWRITER_H

#include <QtTest>
#define private public
#include <../src/romeo/model/core/writer.h>
#include <../src/romeo/model/core/modelcore.h>

using namespace romeo::model::core;

class TestWriter : public QObject
{
    Q_OBJECT

public:
    explicit TestWriter(QObject *parent = 0);

private slots:
    void getInstance();
    void saveLists();
    void saveDataset();
};


#endif // TESTWRITER_H
