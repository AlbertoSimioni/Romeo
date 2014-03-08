#include "testcontroller.h"
#include "ui_protocoldialog.h"
#include "ui_newalgorithmdialog.h"
#include "ui_newfeaturedialog.h"
#include "ui_newdatasetdialog.h"

TestController::TestController(QObject *parent) :
    QObject(parent){
}


void TestController::getInstance(){
    QCOMPARE(Controller::getInstance(),Controller::getInstance());
}


void TestController::checkProtocolName(){
    Controller *controller = Controller::getInstance();

    controller->checkProtocolName(QString("notExists"));
    QCOMPARE(controller->protocolDialog->ui->errorLabel->isHidden(),true);

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


    controller->checkProtocolName(staticProtName);
    QCOMPARE(controller->protocolDialog->ui->next1->isEnabled(),false);
}

void TestController::checkAlgorithmName(){
    Controller *controller = Controller::getInstance();

    controller->checkAlgorithmName(QString("notExists"));
    QCOMPARE(controller->newAlgorithmDialog->ui->errorLabel->isHidden(),true);

    QString algName = "algName";
    QString algDescr = "algDescription";
    QList<algorithms::AbstractAlgorithm::AlgorithmParameter> paramList;
    QList<QString> algParameters;
    int clusterNum = 1;
    QString algDylp = "dylp";
    QString algDyfn = "dyfn";
    UserDefinedAlgorithm *myAlg = new UserDefinedAlgorithm(paramList,algName,algDescr,algDylp,algDyfn);

    AlgorithmsList *algList = AlgorithmsList::getInstance();

    algList->addAlgorithm(myAlg);


    controller->checkAlgorithmName(algName);
    QCOMPARE(controller->newAlgorithmDialog->ui->okCancel->button(QDialogButtonBox::Ok)->isEnabled(),false);


}

void TestController::checkFeatureName(){
    Controller *controller = Controller::getInstance();

    controller->checkFeatureName(QString("notExists"));
    QCOMPARE(controller->newFeatureDialog->ui->errorLabel->isHidden(),true);

    features::FeaturesList *list = features::FeaturesList::getInstance();

    QString featName = "featName";
    features::FirstOrderFeature *foFeat = new features::FirstOrderFeature(featName,QString("fodylp"),QString("fodyfn"),QString("fodescription"));

    list->addFeature(foFeat);

    controller->checkFeatureName(featName);
    QCOMPARE(controller->newFeatureDialog->ui->okCancel->button(QDialogButtonBox::Ok)->isEnabled(),false);


}

void TestController::checkDatasetName(){

    Controller *controller = Controller::getInstance();

    controller->checkDatasetName(QString("notExists"));
    QCOMPARE(controller->newDatasetDialog->ui->ErrorLabel->isHidden(),true);

    DatasetsList *list = DatasetsList::getInstance();

    QString datasetName = "dataset2D";
    list->addDataset(datasetName,romeo::model::TYPE2D);

    controller->checkDatasetName(datasetName);
    QCOMPARE(controller->newDatasetDialog->ui->okCancel->button(QDialogButtonBox::Ok)->isEnabled(),false);


}

void TestController::checkSubjectName(){

}

void TestController::addProtocol(){

    Controller *controller = Controller::getInstance();

    controller->checkProtocolName(QString("notExists"));
    QCOMPARE(controller->protocolDialog->ui->errorLabel->isHidden(),true);

    QString algName = "algName";
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


    controller->addProtocol(staticProtName,staticProtDescr,testStaticProtocol,features,algName,STATIC,staticProtWindow,staticProtDistance,clusterNum,algParameters);


    ProtocolsList *protList = ProtocolsList::getInstance();

    QVERIFY(protList->getProtocol(staticProtName) != false);

}


//QTEST_MAIN(TestController)
