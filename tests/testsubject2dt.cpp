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

    QString name = "videoSubj";
    QString dataPath = dataTest.absolutePath().append("/images/video.avi");
    QString maskPath = "";

    romeo::model::datasets::Subject2DT *s2dt=new Subject2DT(name,dataPath,maskPath);
    QFETCH(romeo::model::InputFormat,type);
    QCOMPARE(s2dt->getType(),type);
    delete s2dt;
}
