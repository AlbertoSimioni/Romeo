#include "testsubject2d.h"

TestSubject2D::TestSubject2D(QObject *parent) :
    QObject(parent){
}


void TestSubject2D::getType_data(){
    QTest::addColumn<romeo::model::InputFormat>("type");

    QTest::newRow("Subject1")<<romeo::model::TYPE2D;
}


void TestSubject2D::getType(){
    QDir dataTest = QDir::current();
    dataTest.cd("..");
    dataTest.cd("..");
    dataTest.cd("tests");

    QString name = "subjName";
    QString dataPath = dataTest.absolutePath().append("/images/image.tif");
    QString maskPath = dataTest.absolutePath().append("/images/mask.tif");

    Subject2D *s2d=new Subject2D(name,dataPath,maskPath);
    QFETCH(romeo::model::InputFormat,type);
    QCOMPARE(s2d->getType(),type);
    delete s2d;
}
