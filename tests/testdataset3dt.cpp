#include "testdataset3dt.h"

TestDataset3DT::TestDataset3DT(QObject *parent) :
    QObject(parent){
}


void TestDataset3DT::makeSubject_data(){

    QTest::addColumn<QString>("name");
    QTest::addColumn<QString>("fileSubject");
    QTest::addColumn<QString>("mask");

    QTest::newRow("dataset1")<<"name1"<<"fileSubject1"<<"mask1";
    QTest::newRow("dataset2")<<"name2"<<"fileSubject2"<<"mask2";
    QTest::newRow("dataset3")<<"name3"<<"fileSubject3"<<"mask3";


}

void TestDataset3DT::makeSubject(){
    QString string ="a";
    Dataset3DT *ds3dt=new Dataset3DT(string);

    QFETCH(QString,name);
    QFETCH(QString,fileSubject);
    QFETCH(QString,mask);

    AbstractSubject *sub=ds3dt->makeSubject(name,fileSubject,mask);
    QCOMPARE(sub->getName(),name);
    QCOMPARE(sub->getSubject(),fileSubject);
    QCOMPARE(sub->getMask(),mask);
}

void TestDataset3DT::getType_data(){
    QTest::addColumn<romeo::model::InputFormat>("Type");

    QTest::newRow("dataset1")<<romeo::model::TYPE3DT;
}

void TestDataset3DT::getType(){
    QString string ="a";
    Dataset3DT *ds2d=new Dataset3DT(string);

    QFETCH(romeo::model::InputFormat,Type);

    QCOMPARE(ds2d->getType(),Type);
    }


void TestDataset3DT::getProtocolsType_data(){
    QTest::addColumn<romeo::model::protocols::ProtocolType>("Type");

    QTest::newRow("dataset1")<<romeo::model::protocols::DYNAMIC;
}

void TestDataset3DT::getProtocolsType(){
    QString string ="a";
    Dataset3DT *ds3dt=new Dataset3DT(string);

    QFETCH(romeo::model::protocols::ProtocolType,Type);

    QCOMPARE(ds3dt->getProtocolsType(),Type);
    }

//QTEST_MAIN(TestDataset3DT)

