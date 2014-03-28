#include "testdataset2dt.h"

TestDataset2DT::TestDataset2DT(QObject *parent) :
    QObject(parent){
}


void TestDataset2DT::makeSubject_data(){
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

void TestDataset2DT::makeSubject(){
    QString string ="ds2t";
    Dataset2DT *ds2dt=new Dataset2DT(string);

    QFETCH(QString,name);
    QFETCH(QString,fileSubject);
    QFETCH(QString,mask);

    AbstractSubject *sub=ds2dt->makeSubject(name,fileSubject,mask);
    QCOMPARE(sub->getName(),name);
    QCOMPARE(sub->getSubject(),fileSubject);
    QCOMPARE(sub->getMask(),mask);
    delete ds2dt;
}

void TestDataset2DT::getType_data(){
    QTest::addColumn<romeo::model::InputFormat>("Type");

    QTest::newRow("dataset1")<<romeo::model::TYPE2DT;
}

void TestDataset2DT::getType(){
    QString string ="ds2t";
    Dataset2DT *ds2dt=new Dataset2DT(string);

    QFETCH(romeo::model::InputFormat,Type);

    QCOMPARE(ds2dt->getType(),Type);
    delete ds2dt;
}


void TestDataset2DT::getProtocolsType_data(){
    QTest::addColumn<romeo::model::protocols::ProtocolType>("Type");

    QTest::newRow("dataset1")<<romeo::model::protocols::DYNAMIC;
}

void TestDataset2DT::getProtocolsType(){
    QString string ="ds2t";
    Dataset2DT *ds2dt=new Dataset2DT(string);

    QFETCH(romeo::model::protocols::ProtocolType,Type);

    QCOMPARE(ds2dt->getProtocolsType(),Type);
    delete ds2dt;
}
