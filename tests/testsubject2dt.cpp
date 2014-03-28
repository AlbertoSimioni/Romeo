#include "testsubject2dt.h"

TestSubject2DT::TestSubject2DT(QObject *parent) :
    QObject(parent){
}


void TestSubject2DT::getType_data(){
    QTest::addColumn<romeo::model::InputFormat>("type");

    QTest::newRow("Subject1")<<romeo::model::TYPE2DT;
}


void TestSubject2DT::getType(){
    QDir dataTest = QDir::current();
    dataTest.cd("..");
    dataTest.cd("..");
    dataTest.cd("tests");

    QString name = "subjName";
    QString dataPath = dataTest.absolutePath().append("/images/image.tif");
    QString maskPath = dataTest.absolutePath().append("/images/mask.tif");

    romeo::model::datasets::Subject2DT *s2dt=new Subject2DT(name,dataPath,maskPath);
    QFETCH(romeo::model::InputFormat,type);
    QCOMPARE(s2dt->getType(),type);
    delete s2dt;
}
