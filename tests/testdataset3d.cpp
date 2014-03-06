#include "testdataset3d.h"

TestDataset3D::TestDataset3D(QObject *parent) :
    QObject(parent){
}


void TestDataset3D::makeSubject_data(){

    QTest::addColumn<QString>("name");
    QTest::addColumn<QString>("fileSubject");
    QTest::addColumn<QString>("mask");

    QTest::newRow("dataset1")<<"name1"<<"fileSubject1"<<"mask1";
    QTest::newRow("dataset2")<<"name2"<<"fileSubject2"<<"mask2";
    QTest::newRow("dataset3")<<"name3"<<"fileSubject3"<<"mask3";


}

void TestDataset3D::makeSubject(){
    QString string ="a";
    Dataset3D *ds3d=new Dataset3D(string);

    QFETCH(QString,name);
    QFETCH(QString,fileSubject);
    QFETCH(QString,mask);

    AbstractSubject *sub=ds3d->makeSubject(name,fileSubject,mask);
    QCOMPARE(sub->getName(),name);
    QCOMPARE(sub->getSubject(),fileSubject);
    QCOMPARE(sub->getMask(),mask);
}

void TestDataset3D::getType_data(){
    QTest::addColumn<romeo::model::InputFormat>("Type");

    QTest::newRow("dataset1")<<romeo::model::TYPE3D;
}

void TestDataset3D::getType(){
    QString string ="a";
    Dataset3D *ds3d=new Dataset3D(string);

    QFETCH(romeo::model::InputFormat,Type);

    QCOMPARE(ds3d->getType(),Type);
    }


void TestDataset3D::getProtocolsType_data(){
    QTest::addColumn<romeo::model::protocols::ProtocolType>("Type");

    QTest::newRow("dataset1")<<romeo::model::protocols::STATIC;
}

void TestDataset3D::getProtocolsType(){
    QString string ="a";
    Dataset3D *ds3d=new Dataset3D(string);

    QFETCH(romeo::model::protocols::ProtocolType,Type);

    QCOMPARE(ds3d->getProtocolsType(),Type);
    }


//QTEST_MAIN(TestDataset3D)

