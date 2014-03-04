#include "testwriter.h"

TestWriter::TestWriter(QObject *parent) :
    QObject(parent){
}


void TestWriter::getInstance(){
    Writer *writer = new Writer(0);
    QCOMPARE(writer->getInstance(0),writer->getInstance(0));
    Writer *writer2 = new Writer(0);
    QCOMPARE(writer2->getInstance(0),writer2->getInstance(writer));
    Writer *writer3 = new Writer(0);
    QCOMPARE(writer3->getInstance(writer),writer3->getInstance(0));
}


void TestWriter::saveLists(){
    ModelCore *mc = new ModelCore(0);
    Writer *writer = new Writer(0);

    QVERIFY(writer->saveDatasetsList()!=false);
    QFile datasetsFile(ModelCore::getDataHome().absolutePath().append("/datasets.xml"));
    QCOMPARE(datasetsFile.open(QFile::ReadOnly),true);
    datasetsFile.close();

    QVERIFY(writer->saveProtocolsList()!=false);
    QFile protocolsFile(ModelCore::getDataHome().absolutePath().append("/protocols.xml"));
    QCOMPARE(protocolsFile.open(QFile::ReadOnly),true);
    protocolsFile.close();

    QVERIFY(writer->saveFeaturesList()!=false);
    QFile featuresFile(ModelCore::getDataHome().absolutePath().append("/features.xml"));
    QCOMPARE(featuresFile.open(QFile::ReadOnly),true);
    featuresFile.close();

    QVERIFY(writer->saveAlgorithmsList()!=false);
    QFile algorithmsFile(ModelCore::getDataHome().absolutePath().append("/algorithms.xml"));
    QCOMPARE(algorithmsFile.open(QFile::ReadOnly),true);
    algorithmsFile.close();
}

void TestWriter::saveDataset(){
    /*ModelCore *mc = new ModelCore(0);
    Writer *writer = new Writer(0);

    QVERIFY(writer->saveDataset(QString("name"))!=false);
*/}


//QTEST_MAIN(TestWriter)
