#include "testsubject2d.h"

TestSubject2D::TestSubject2D(QObject *parent) :
    QObject(parent){
}


void TestSubject2D::getType_data(){
    QTest::addColumn<romeo::model::InputFormat>("type");

    QTest::newRow("Subject1")<<romeo::model::TYPE2D;
}


void TestSubject2D::getType(){
    QString a ="a";
    QString b="b";
    QString c ="c";
    romeo::model::datasets::Subject2D *s2d=new Subject2D(a,b,c);
    QFETCH(romeo::model::InputFormat,type);
    QCOMPARE(s2d->getType(),type);
    delete s2d;
}
