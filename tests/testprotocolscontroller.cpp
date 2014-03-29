#include "testprotocolscontroller.h"
#include "ui_protocoldialog.h"

TestProtocolsController::TestProtocolsController(QObject *parent) :
    QObject(parent){
}


void TestProtocolsController::getInstance(){
    DatasetsController *controller = DatasetsController::getInstance();
    QCOMPARE(ProtocolsController::getInstance(),ProtocolsController::getInstance());
}


void TestProtocolsController::checkProtocolName(){
    DatasetsController *controller = DatasetsController::getInstance();
    ProtocolsController *protocolscontroller = ProtocolsController::getInstance();

    protocolscontroller->checkProtocolName(QString("notExists"));
    QCOMPARE(protocolscontroller->protocolDialog->ui->errorLabel->isHidden(),true);

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

    ProtocolsList *protList = ProtocolsList::getInstance();

    protList->addProtocol(staticProtName,staticProtDescr,myAlg,clusterNum,algParameters,feat,testStaticProtocol,STATIC,staticProtWindow,staticProtDistance);


    protocolscontroller->checkProtocolName(staticProtName);
    QCOMPARE(protocolscontroller->protocolDialog->ui->next1->isEnabled(),false);

    protList->removeProtocol(staticProtName);
    delete myAlg;
}


void TestProtocolsController::addProtocol(){
    DatasetsController *controller = DatasetsController::getInstance();
    ProtocolsController *protocolscontroller = ProtocolsController::getInstance();

    protocolscontroller->checkProtocolName(QString("notExists"));
    QCOMPARE(protocolscontroller->protocolDialog->ui->errorLabel->isHidden(),true);

    QString algName = "algName3";
    QString algDescr = "algDescription";
    QList<algorithms::AbstractAlgorithm::AlgorithmParameter> paramList;
    QList<QString> algParameters;
    int clusterNum = 1;
    QString algDylp = "dylp";
    QString algDyfn = "dyfn";
    UserDefinedAlgorithm *myAlg = new UserDefinedAlgorithm(paramList,algName,algDescr,algDylp,algDyfn);

    AlgorithmsList *algList = AlgorithmsList::getInstance();

    algList->addAlgorithm(myAlg);


    QString staticProtName = "staticProtName";
    QString staticProtDescr = "staticProtDescription";
    QList<romeo::model::protocols::features::AbstractFeature*> feat;
    QList<QString> features;
    bool testStaticProtocol = false;
    int staticProtWindow = 5;
    int staticProtDistance = 2;


    protocolscontroller->addProtocol(staticProtName,staticProtDescr,testStaticProtocol,features,algName,STATIC,staticProtWindow,staticProtDistance,clusterNum,algParameters);


    ProtocolsList *protList = ProtocolsList::getInstance();

    QVERIFY(protList->getProtocol(staticProtName) != false);
    delete myAlg;
}

void TestProtocolsController::deleteProtocol(){
    DatasetsController *controller = DatasetsController::getInstance();
    ProtocolsController *protocolscontroller = ProtocolsController::getInstance();

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

    ProtocolsList *protList = ProtocolsList::getInstance();

    StaticProtocol *sp = new StaticProtocol(staticProtName,staticProtDescr,myAlg,clusterNum,algParameters,feat,testStaticProtocol,staticProtWindow,staticProtDistance);

    protList->addProtocol(staticProtName,staticProtDescr,myAlg,clusterNum,algParameters,feat,testStaticProtocol,STATIC,staticProtWindow,staticProtDistance);

    protocolscontroller->deleteProtocol(staticProtName);

    QCOMPARE(protList->getProtocolsList().indexOf(sp),-1);

    delete myAlg;
    delete sp;
}

void TestProtocolsController::associateProtocol(){
    DatasetsController *controller = DatasetsController::getInstance();

    ProtocolsController *protocolscontroller = ProtocolsController::getInstance();

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

    ProtocolsList *protList = ProtocolsList::getInstance();

    protList->addProtocol(staticProtName,staticProtDescr,myAlg,clusterNum,algParameters,feat,testStaticProtocol,STATIC,staticProtWindow,staticProtDistance);

    QString datName = "myDataset";
    Dataset2D *ds2d = new Dataset2D(datName);
    AbstractDataset *prev = protocolscontroller->mainWindow->getDatasetPanel()->getCurrentDataset();
    protocolscontroller->mainWindow->getDatasetPanel()->setCurrentDataset(ds2d);

    protocolscontroller->associateProtocol(staticProtName);

    QVERIFY(protocolscontroller->mainWindow->getDatasetPanel()->getCurrentDataset()->getProtocol(staticProtName) != 0);

    protocolscontroller->mainWindow->getDatasetPanel()->setCurrentDataset(prev);

    delete myAlg;
    //delete ds2d;
}

void TestProtocolsController::removeProtocolAssociation(){
    DatasetsController *controller = DatasetsController::getInstance();

    ProtocolsController *protocolscontroller = ProtocolsController::getInstance();

    QString algName = "algName";
    QString algDescr = "algDescription";
    QList<algorithms::AbstractAlgorithm::AlgorithmParameter> paramList;
    QList<QString> algParameters;
    int clusterNum = 1;
    QString algDylp = "dylp";
    QString algDyfn = "dyfn";
    UserDefinedAlgorithm *myAlg = new UserDefinedAlgorithm(paramList,algName,algDescr,algDylp,algDyfn);

    QString staticProtName = "oldProtName";
    QString staticProtDescr = "staticProtDescription";
    QList<romeo::model::protocols::features::AbstractFeature*> feat;
    bool testStaticProtocol = false;
    int staticProtWindow = 5;
    int staticProtDistance = 2;

    StaticProtocol *sp = new StaticProtocol(staticProtName,staticProtDescr,myAlg,clusterNum,algParameters,feat,testStaticProtocol,staticProtWindow,staticProtDistance);

    QString datName = "myDataset";
    AbstractDataset *prev = protocolscontroller->mainWindow->getDatasetPanel()->getCurrentDataset();
    Dataset2D *ds2d = new Dataset2D(datName);
    ds2d->associateProtocol(sp);

    ProtocolsList *protList = ProtocolsList::getInstance();

    protList->addProtocol(staticProtName,staticProtDescr,myAlg,clusterNum,algParameters,feat,testStaticProtocol,STATIC,staticProtWindow,staticProtDistance);


    protocolscontroller->mainWindow->getDatasetPanel()->setCurrentDataset(ds2d);

    protocolscontroller->removeProtocolAssociation(staticProtName);

    QCOMPARE(protocolscontroller->mainWindow->getDatasetPanel()->getCurrentDataset()->getAssociatedProtocolsList().indexOf(sp),-1);

    protocolscontroller->mainWindow->getDatasetPanel()->setCurrentDataset(prev);

    //delete myAlg;
    //delete sp;
    //delete ds2d;
}


void TestProtocolsController::modifyProtocol(){
    DatasetsController *controller = DatasetsController::getInstance();

    ProtocolsController *protocolscontroller = ProtocolsController::getInstance();

    QString algName = "algName";
    QString algDescr = "algDescription";
    QList<algorithms::AbstractAlgorithm::AlgorithmParameter> paramList;
    QList<QString> algParameters;
    int clusterNum = 1;
    QString algDylp = "dylp";
    QString algDyfn = "dyfn";
    UserDefinedAlgorithm *myAlg = new UserDefinedAlgorithm(paramList,algName,algDescr,algDylp,algDyfn);

    QString staticProtName = "oldProtName";
    QString staticProtName2 = "newProtName";
    QString staticProtDescr = "staticProtDescription";
    QList<romeo::model::protocols::features::AbstractFeature*> feat;
    QList<QString> features;
    bool testStaticProtocol = false;
    int staticProtWindow = 5;
    int staticProtDistance = 2;

    StaticProtocol *sp = new StaticProtocol(staticProtName,staticProtDescr,myAlg,clusterNum,algParameters,feat,testStaticProtocol,staticProtWindow,staticProtDistance);

    ProtocolsList *protList = ProtocolsList::getInstance();

    protList->addProtocol(staticProtName,staticProtDescr,myAlg,clusterNum,algParameters,feat,testStaticProtocol,STATIC,staticProtWindow,staticProtDistance);
    protList->addProtocol(staticProtName2,staticProtDescr,myAlg,clusterNum,algParameters,feat,testStaticProtocol,STATIC,staticProtWindow,staticProtDistance);

    AbstractDataset *prev = protocolscontroller->mainWindow->getDatasetPanel()->getCurrentDataset();
    QString datName = "myDataset";
    Dataset2D *ds2d = new Dataset2D(datName);
    protocolscontroller->mainWindow->getDatasetPanel()->setCurrentDataset(ds2d);

    ds2d->associateProtocol(sp);

    protocolscontroller->modifyProtocol(staticProtName,staticProtName2,staticProtDescr,testStaticProtocol,features,algName,STATIC,staticProtWindow,staticProtDistance,clusterNum,algParameters);

    QVERIFY(protList->getProtocol(staticProtName) == false);
    QVERIFY(protList->getProtocol(staticProtName2) != false);

    protocolscontroller->mainWindow->getDatasetPanel()->setCurrentDataset(prev);

    delete myAlg;
    delete sp;
    //delete ds2d;
}


/*void TestProtocolsController::viewNewProtocolDialog(){
    ProtocolsController *protocolscontroller = ProtocolsController::getInstance();

    protocolscontroller->viewNewProtocolDialog();

    QCOMPARE(protocolscontroller->protocolDialog->result(),1);
}
*/
