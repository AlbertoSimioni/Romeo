#include "testresult.h"

TestResult::TestResult(QObject *parent) :
    QObject(parent){
}


void TestResult::getExecutionDate_data(){
    QTest::addColumn<QDateTime>("data");

    QTest::newRow("ResultDataOK")<<QDateTime(QDate(2013,2,24));
    QTest::newRow("ResultDataFAIL")<<QDateTime(QDate(2013,2,25));
}


void TestResult::getExecutionDate(){
    QString path="b";
    QDateTime dataToCompare=QDateTime(QDate(2013,2,24));
    QFETCH(QDateTime,data);
    Result *r=new Result(data,path);
    if(data==QDateTime(QDate(2013,2,25)))
        QVERIFY(r->getExecutionDate()!=dataToCompare);
    else{
    QCOMPARE(r->getExecutionDate(),dataToCompare);
    }
    delete r;
}

void TestResult::getResultPath(){
    QString c1="ciao";
    QString c2="IAO";
    QString c3="Ciao";

    QString pathToCompare="ciao";
    Result *r=new Result(c1);

    QCOMPARE(r->getResultPath(),c1);
    QVERIFY(r->getResultPath()!=c2);
    QVERIFY(r->getResultPath()!=c3);

    delete r;
}

//QTEST_MAIN(TestResult)

