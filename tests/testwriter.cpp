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


void TestWriter::saveDatasetsList(){
    DatasetsController *controller = DatasetsController::getInstance();
    DatasetsList *list = DatasetsList::getInstance();

    list->addDataset(QString("dataset2D"),romeo::model::TYPE2D);
    list->addDataset(QString("dataset2DT"),romeo::model::TYPE2DT);
    list->addDataset(QString("dataset3D"),romeo::model::TYPE3D);
    list->addDataset(QString("dataset3DT"),romeo::model::TYPE3DT);



    ModelCore *mc =  ModelCore::getInstance();

    Writer *writer = Writer::getInstance();

    QVERIFY(writer->saveDatasetsList()!=false);
    QFile datasetsFile(ModelCore::getDataHome().absolutePath().append("/datasets.xml"));
    QCOMPARE(datasetsFile.open(QFile::ReadOnly),true);
    datasetsFile.close();

}

void TestWriter::saveProtocolsList(){
    DatasetsController *controller = DatasetsController::getInstance();
    QString algName = "algName";
    QString algDescr = "algDescription";
    QList<algorithms::AbstractAlgorithm::AlgorithmParameter> paramList;
    QList<QString> algParameters;
    int clusterNum = 1;
    QString algDylp = "dylp";
    QString algDyfn = "dyfn";
    UserDefinedAlgorithm *myAlg = new UserDefinedAlgorithm(paramList,algName,algDescr,algDylp,algDyfn);

    QString staticProtName = "staticProtName";
    QString staticProtDescr = "staticProtDescription";
    QList<romeo::model::protocols::features::AbstractFeature*> feat;
    bool testStaticProtocol = false;
    int staticProtWindow = 5;
    int staticProtDistance = 2;

    QString dynamicProtName = "dynamicProtName";
    QString dynamicProtDescr = "dynamicProtDescription";
    QList<romeo::model::protocols::features::AbstractFeature*> feat2;
    bool testDynamicProtocol = true;

    ProtocolsList *protList = ProtocolsList::getInstance();


    protList->addProtocol(staticProtName,staticProtDescr,myAlg,clusterNum,algParameters,feat,testStaticProtocol,STATIC,staticProtWindow,staticProtDistance);
    protList->addProtocol(dynamicProtName,dynamicProtDescr,myAlg,clusterNum,algParameters,feat2,testDynamicProtocol,DYNAMIC);


    ModelCore *mc =  ModelCore::getInstance();

    Writer *writer = Writer::getInstance();

    QVERIFY(writer->saveProtocolsList()!=false);
    QFile protocolsFile(ModelCore::getDataHome().absolutePath().append("/protocols.xml"));
    QCOMPARE(protocolsFile.open(QFile::ReadOnly),true);
    protocolsFile.close();
}

void TestWriter::saveAlgorithmsList(){
    DatasetsController *controller = DatasetsController::getInstance();
    AlgorithmsList *list = AlgorithmsList::getInstance();
    QString algName = "name";
    QString algDescr = "description";
    QList<AbstractAlgorithm::AlgorithmParameter> paramList;
    QString algDylp = "dylp";
    QString algDyfn = "dyfn";
    UserDefinedAlgorithm *myAlg = new UserDefinedAlgorithm(paramList,algName,algDescr,algDylp,algDyfn);

    list->addAlgorithm(myAlg);

    ModelCore *mc =  ModelCore::getInstance();

    Writer *writer = Writer::getInstance();

    QVERIFY(writer->saveAlgorithmsList()!=false);
    QFile algorithmsFile(ModelCore::getDataHome().absolutePath().append("/algorithms.xml"));
    QCOMPARE(algorithmsFile.open(QFile::ReadOnly),true);
    algorithmsFile.close();
}

void TestWriter::saveFeaturesList(){
    DatasetsController *controller = DatasetsController::getInstance();
    features::FeaturesList *list = features::FeaturesList::getInstance();

    features::FirstOrderFeature *foFeat = new features::FirstOrderFeature(QString("foname"),QString("fodylp"),QString("fodyfn"),QString("fodescription"));
    features::SecondOrderFeature *soFeat = new features::SecondOrderFeature(QString("soname"),QString("sodylp"),QString("sodyfn"),QString("sodescription"));
    features::DynamicFeature *dynFeat = new features::DynamicFeature(QString("dynname"),QString("dyndylp"),QString("dyndyfn"),QString("dyndescription"));

    list->addFeature(foFeat);
    list->addFeature(soFeat);
    list->addFeature(dynFeat);

    ModelCore *mc =  ModelCore::getInstance();

    Writer *writer = Writer::getInstance();

    QVERIFY(writer->saveFeaturesList()!=false);
    QFile featuresFile(ModelCore::getDataHome().absolutePath().append("/features.xml"));
    QCOMPARE(featuresFile.open(QFile::ReadOnly),true);
    featuresFile.close();
}

void TestWriter::saveDataset(){
    DatasetsController *controller = DatasetsController::getInstance();
    DatasetsList *list = DatasetsList::getInstance();

    ModelCore *mc =  ModelCore::getInstance();

    Writer *writer = Writer::getInstance();

    QVERIFY(writer->saveDataset(QString("dataset2D"))!=false);
    QVERIFY(writer->saveDataset(QString("dataset2DT"))!=false);
    QVERIFY(writer->saveDataset(QString("dataset3D"))!=false);
    QVERIFY(writer->saveDataset(QString("dataset3DT"))!=false);
}

void TestWriter::writeDatasetProtocols(){
    DatasetsController *controller = DatasetsController::getInstance();
    QString algName = "algName";
    QString algDescr = "algDescription";
    QList<algorithms::AbstractAlgorithm::AlgorithmParameter> paramList;
    QList<QString> algParameters;
    int clusterNum = 1;
    QString algDylp = "dylp";
    QString algDyfn = "dyfn";
    UserDefinedAlgorithm *myAlg = new UserDefinedAlgorithm(paramList,algName,algDescr,algDylp,algDyfn);

    QString staticProtName = "staticProtName";
    QString staticProtDescr = "staticProtDescription";
    QList<romeo::model::protocols::features::AbstractFeature*> feat;
    bool testStaticProtocol = false;
    int staticProtWindow = 5;
    int staticProtDistance = 2;

    QString dynamicProtName = "dynamicProtName";
    QString dynamicProtDescr = "dynamicProtDescription";
    QList<romeo::model::protocols::features::AbstractFeature*> feat2;
    bool testDynamicProtocol = true;

    QString name2d = "name2d";
    Dataset2D *dataset2d = new Dataset2D(name2d);
    StaticProtocol *sp = new StaticProtocol(staticProtName,staticProtDescr,myAlg,clusterNum,algParameters,feat,testStaticProtocol,staticProtWindow,staticProtDistance);

    QString name2dt = "name2dt";
    Dataset2DT *dataset2dt = new Dataset2DT(name2dt);
    DynamicProtocol *dp = new DynamicProtocol(dynamicProtName,dynamicProtDescr,myAlg,clusterNum,algParameters,feat2,testDynamicProtocol);

    QString name3d = "name3d";
    Dataset3D *dataset3d = new Dataset3D(name2d);

    QString name3dt = "name3dt";
    Dataset3DT *dataset3dt = new Dataset3DT(name2dt);


    dataset2d->associateProtocol(sp);
    dataset2dt->associateProtocol(dp);
    dataset3d->associateProtocol(sp);
    dataset3dt->associateProtocol(dp);

    dataset2d->addResult(name2d,QString("path"));

    ModelCore *mc =  ModelCore::getInstance();

    Writer *writer = Writer::getInstance();

    QXmlStreamWriter xmlwriter;
    QFile file(ModelCore::getDataHome().absolutePath().append("/datasetprotocols.xml"));
    QVERIFY(file.open(QFile::ReadWrite) != false);

    xmlwriter.setDevice(&file);
    xmlwriter.setAutoFormatting(true);
    xmlwriter.writeStartDocument();

    writer->writeDatasetProtocols(dataset2d,xmlwriter);

    writer->writeDatasetProtocols(dataset2dt,xmlwriter);

    writer->writeDatasetProtocols(dataset3d,xmlwriter);

    writer->writeDatasetProtocols(dataset3dt,xmlwriter);

    file.close();
}
