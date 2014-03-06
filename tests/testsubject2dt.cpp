#include "testsubject2dt.h"

TestSubject2DT::TestSubject2DT(QObject *parent) :
    QObject(parent){
}


void TestSubject2DT::getType_data(){
    QTest::addColumn<romeo::model::InputFormat>("type");

    QTest::newRow("Subject1")<<romeo::model::TYPE2DT;
}


void TestSubject2DT::getType(){
    QString a ="a";
    QString b="b";
    QString c ="c";
    romeo::model::datasets::Subject2DT *s2dt=new Subject2DT(a,b,c);
    QFETCH(romeo::model::InputFormat,type);
    QCOMPARE(s2dt->getType(),type);
}

//QTEST_MAIN(TestSubject2DT)

