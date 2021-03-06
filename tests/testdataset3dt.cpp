#include "testdataset3dt.h"

TestDataset3DT::TestDataset3DT(QObject *parent) :
    QObject(parent){
}


void TestDataset3DT::makeSubject_data(){
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

void TestDataset3DT::makeSubject(){
    QString string ="dsname";
    Dataset3DT *ds3dt=new Dataset3DT(string);

    QFETCH(QString,name);
    QFETCH(QString,fileSubject);
    QFETCH(QString,mask);

    AbstractSubject *sub=ds3dt->makeSubject(name,fileSubject,mask);
    QCOMPARE(sub->getName(),name);
    QCOMPARE(sub->getSubject(),fileSubject);
    QCOMPARE(sub->getMask(),mask);
    delete ds3dt;
}

void TestDataset3DT::getType_data(){
    QTest::addColumn<romeo::model::InputFormat>("Type");

    QTest::newRow("dataset1")<<romeo::model::TYPE3DT;
}

void TestDataset3DT::getType(){
    QString string ="dsname";
    Dataset3DT *ds3dt=new Dataset3DT(string);

    QFETCH(romeo::model::InputFormat,Type);

    QCOMPARE(ds3dt->getType(),Type);
    delete ds3dt;
}


void TestDataset3DT::getProtocolsType_data(){
    QTest::addColumn<romeo::model::protocols::ProtocolType>("Type");

    QTest::newRow("dataset1")<<romeo::model::protocols::DYNAMIC;
}

void TestDataset3DT::getProtocolsType(){
    QString string ="dsname";
    Dataset3DT *ds3dt=new Dataset3DT(string);

    QFETCH(romeo::model::protocols::ProtocolType,Type);

    QCOMPARE(ds3dt->getProtocolsType(),Type);
    delete ds3dt;
}
