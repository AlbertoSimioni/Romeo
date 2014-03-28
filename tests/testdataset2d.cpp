#include "testdataset2d.h"

TestDataset2D::TestDataset2D(QObject *parent) :
    QObject(parent){
}


void TestDataset2D::makeSubject_data(){
    QDir dataTest = QDir::current();
    dataTest.cd("..");
    dataTest.cd("..");
    dataTest.cd("tests");
    QString dataPath = dataTest.absolutePath().append("/images/image.tif");
    QString maskPath = dataTest.absolutePath().append("/images/mask.tif");

    QTest::addColumn<QString>("name");
    QTest::addColumn<QString>("fileSubject");
    QTest::addColumn<QString>("mask");

    QTest::newRow("dataset1") << "name1" << dataPath << maskPath;
    QTest::newRow("dataset2") << "name2" << dataPath << maskPath;
    QTest::newRow("dataset3") << "name3" << dataPath << maskPath;


}

void TestDataset2D::makeSubject(){
    QString string ="dsname";
    Dataset2D *ds2d=new Dataset2D(string);

    QFETCH(QString,name);
    QFETCH(QString,fileSubject);
    QFETCH(QString,mask);

    AbstractSubject *sub=ds2d->makeSubject(name,fileSubject,mask);
    QCOMPARE(sub->getName(),name);
    QCOMPARE(sub->getSubject(),fileSubject);
    QCOMPARE(sub->getMask(),mask);
    delete ds2d;
}

void TestDataset2D::getType_data(){
    QTest::addColumn<romeo::model::InputFormat>("Type");

    QTest::newRow("dataset1")<<romeo::model::TYPE2D;
}

void TestDataset2D::getType(){
    QString string ="dsname";
    Dataset2D *ds2d=new Dataset2D(string);

    QFETCH(romeo::model::InputFormat,Type);

    QCOMPARE(ds2d->getType(),Type);
    delete ds2d;
}


void TestDataset2D::getProtocolsType_data(){
    QTest::addColumn<romeo::model::protocols::ProtocolType>("Type");

    QTest::newRow("dataset1")<<romeo::model::protocols::STATIC;
}

void TestDataset2D::getProtocolsType(){
    QString string ="dsname";
    Dataset2D *ds2d=new Dataset2D(string);

    QFETCH(romeo::model::protocols::ProtocolType,Type);

    QCOMPARE(ds2d->getProtocolsType(),Type);
    delete ds2d;
}
