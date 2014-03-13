#include "testsubject3d.h"

TestSubject3D::TestSubject3D(QObject *parent) :
    QObject(parent){
}


void TestSubject3D::getType_data(){
    QTest::addColumn<romeo::model::InputFormat>("type");

    QTest::newRow("Subject1")<<romeo::model::TYPE3D;
}


void TestSubject3D::getType(){
    QString a ="a";
    QString b="b";
    QString c ="c";
    romeo::model::datasets::Subject3D *s3d=new Subject3D(a,b,c);
    QFETCH(romeo::model::InputFormat,type);
    QCOMPARE(s3d->getType(),type);
    delete s3d;
}
