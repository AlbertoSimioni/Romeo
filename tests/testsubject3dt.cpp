#include "testsubject3dt.h"

TestSubject3DT::TestSubject3DT(QObject *parent) :
    QObject(parent){
}


void TestSubject3DT::getType_data(){
    QTest::addColumn<romeo::model::InputFormat>("type");

    QTest::newRow("Subject1")<<romeo::model::TYPE3DT;
}


void TestSubject3DT::getType(){
    QDir dataTest = QDir::current();
    dataTest.cd("..");
    dataTest.cd("..");
    dataTest.cd("tests");

    QString name = "subjName";
    QString dataPath = dataTest.absolutePath().append("/images/image.tif");
    QString maskPath = dataTest.absolutePath().append("/images/mask.tif");

    romeo::model::datasets::Subject3DT *s3dt=new Subject3DT(name,dataPath,maskPath);
    QFETCH(romeo::model::InputFormat,type);
    QCOMPARE(s3dt->getType(),type);
    delete s3dt;
}
