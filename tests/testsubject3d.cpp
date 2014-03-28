#include "testsubject3d.h"

TestSubject3D::TestSubject3D(QObject *parent) :
    QObject(parent){
}


void TestSubject3D::getType_data(){
    QTest::addColumn<romeo::model::InputFormat>("type");

    QTest::newRow("Subject1")<<romeo::model::TYPE3D;
}


void TestSubject3D::getType(){
    QDir dataTest = QDir::current();
    dataTest.cd("..");
    dataTest.cd("..");
    dataTest.cd("tests");

    QString name = "subjName";
    QString dataPath = dataTest.absolutePath().append("/images/image.tif");
    QString maskPath = dataTest.absolutePath().append("/images/mask.tif");

    romeo::model::datasets::Subject3D *s3d=new Subject3D(name,dataPath,maskPath);
    QFETCH(romeo::model::InputFormat,type);
    QCOMPARE(s3d->getType(),type);
    delete s3d;
}
