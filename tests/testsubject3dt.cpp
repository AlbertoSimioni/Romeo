#include "testsubject3dt.h"

TestSubject3DT::TestSubject3DT(QObject *parent) :
    QObject(parent){
}


void TestSubject3DT::getType_data(){
    QTest::addColumn<romeo::model::InputFormat>("type");

    QTest::newRow("Subject1")<<romeo::model::TYPE3DT;
}


void TestSubject3DT::getType(){
    QString a ="a";
    QString b="b";
    QString c ="c";
    romeo::model::datasets::Subject3DT *s3dt=new Subject3DT(a,b,c);
    QFETCH(romeo::model::InputFormat,type);
    QCOMPARE(s3dt->getType(),type);
}

//QTEST_MAIN(TestSubject3DT)

