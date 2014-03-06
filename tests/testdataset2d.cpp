#include "testdataset2d.h"

TestDataset2D::TestDataset2D(QObject *parent) :
    QObject(parent){
}


void TestDataset2D::makeSubject_data(){

    QTest::addColumn<QString>("name");
    QTest::addColumn<QString>("fileSubject");
    QTest::addColumn<QString>("mask");

    QTest::newRow("dataset1")<<"name1"<<"fileSubject1"<<"mask1";
    QTest::newRow("dataset2")<<"name2"<<"fileSubject2"<<"mask2";
    QTest::newRow("dataset3")<<"name3"<<"fileSubject3"<<"mask3";


}

void TestDataset2D::makeSubject(){
    QString string ="a";
    Dataset2D *ds2d=new Dataset2D(string);

    QFETCH(QString,name);
    QFETCH(QString,fileSubject);
    QFETCH(QString,mask);

    AbstractSubject *sub=ds2d->makeSubject(name,fileSubject,mask);
    QCOMPARE(sub->getName(),name);
    QCOMPARE(sub->getSubject(),fileSubject);
    QCOMPARE(sub->getMask(),mask);
}

void TestDataset2D::getType_data(){
    QTest::addColumn<romeo::model::InputFormat>("Type");

    QTest::newRow("dataset1")<<romeo::model::TYPE2D;
}

void TestDataset2D::getType(){
    QString string ="a";
    Dataset2D *ds2d=new Dataset2D(string);

    QFETCH(romeo::model::InputFormat,Type);

    QCOMPARE(ds2d->getType(),Type);
    }


void TestDataset2D::getProtocolsType_data(){
    QTest::addColumn<romeo::model::protocols::ProtocolType>("Type");

    QTest::newRow("dataset1")<<romeo::model::protocols::STATIC;
}

void TestDataset2D::getProtocolsType(){
    QString string ="a";
    Dataset2D *ds2d=new Dataset2D(string);

    QFETCH(romeo::model::protocols::ProtocolType,Type);

    QCOMPARE(ds2d->getProtocolsType(),Type);
    }


//QTEST_MAIN(TestDataset2D)

