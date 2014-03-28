#include "testdataset3d.h"

TestDataset3D::TestDataset3D(QObject *parent) :
    QObject(parent){
}


void TestDataset3D::makeSubject_data(){
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

void TestDataset3D::makeSubject(){
    QString string ="dsname";
    Dataset3D *ds3d=new Dataset3D(string);

    QFETCH(QString,name);
    QFETCH(QString,fileSubject);
    QFETCH(QString,mask);

    AbstractSubject *sub=ds3d->makeSubject(name,fileSubject,mask);
    QCOMPARE(sub->getName(),name);
    QCOMPARE(sub->getSubject(),fileSubject);
    QCOMPARE(sub->getMask(),mask);
    delete ds3d;
}

void TestDataset3D::getType_data(){
    QTest::addColumn<romeo::model::InputFormat>("Type");

    QTest::newRow("dataset1")<<romeo::model::TYPE3D;
}

void TestDataset3D::getType(){
    QString string ="dsname";
    Dataset3D *ds3d=new Dataset3D(string);

    QFETCH(romeo::model::InputFormat,Type);

    QCOMPARE(ds3d->getType(),Type);
    delete ds3d;
}


void TestDataset3D::getProtocolsType_data(){
    QTest::addColumn<romeo::model::protocols::ProtocolType>("Type");

    QTest::newRow("dataset1")<<romeo::model::protocols::STATIC;
}

void TestDataset3D::getProtocolsType(){
    QString string ="dsname";
    Dataset3D *ds3d=new Dataset3D(string);

    QFETCH(romeo::model::protocols::ProtocolType,Type);

    QCOMPARE(ds3d->getProtocolsType(),Type);
    delete ds3d;
}
