#include "testdataset2dt.h"

TestDataset2DT::TestDataset2DT(QObject *parent) :
    QObject(parent){
}


void TestDataset2DT::makeSubject_data(){

    QTest::addColumn<QString>("name");
    QTest::addColumn<QString>("fileSubject");
    QTest::addColumn<QString>("mask");

    QTest::newRow("dataset1")<<"name1"<<"fileSubject1"<<"mask1";
    QTest::newRow("dataset2")<<"name2"<<"fileSubject2"<<"mask2";
    QTest::newRow("dataset3")<<"name3"<<"fileSubject3"<<"mask3";


}

void TestDataset2DT::makeSubject(){
    QString string ="a";
    Dataset2DT *ds2dt=new Dataset2DT(string);

    QFETCH(QString,name);
    QFETCH(QString,fileSubject);
    QFETCH(QString,mask);

    AbstractSubject *sub=ds2dt->makeSubject(name,fileSubject,mask);
    QCOMPARE(sub->getName(),name);
    QCOMPARE(sub->getSubject(),fileSubject);
    QCOMPARE(sub->getMask(),mask);
}

void TestDataset2DT::getType_data(){
    QTest::addColumn<romeo::model::InputFormat>("Type");

    QTest::newRow("dataset1")<<romeo::model::TYPE2DT;
}

void TestDataset2DT::getType(){
    QString string ="a";
    Dataset2DT *ds2d=new Dataset2DT(string);

    QFETCH(romeo::model::InputFormat,Type);

    QCOMPARE(ds2d->getType(),Type);
    }


void TestDataset2DT::getProtocolsType_data(){
    QTest::addColumn<romeo::model::protocols::ProtocolType>("Type");

    QTest::newRow("dataset1")<<romeo::model::protocols::DYNAMIC;
}

void TestDataset2DT::getProtocolsType(){
    QString string ="a";
    Dataset2DT *ds2dt=new Dataset2DT(string);

    QFETCH(romeo::model::protocols::ProtocolType,Type);

    QCOMPARE(ds2dt->getProtocolsType(),Type);
    }

//QTEST_MAIN(TestDataset2DT)

