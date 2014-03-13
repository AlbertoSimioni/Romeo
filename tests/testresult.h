#ifndef TESTRESULT_H
#define TESTRESULT_H

#include <QtTest>
#include <../src/romeo/model/datasets/result.h>

using namespace romeo::model::datasets;

class TestResult : public QObject{
    Q_OBJECT

public:
    explicit TestResult(QObject *parent = 0);

private slots:
   void getExecutionDate_data();
   void getExecutionDate();
   void getResultPath();

};


#endif // TESTRESULT_H
