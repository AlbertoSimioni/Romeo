#include "testprotocolscontroller.h"
#include "ui_protocoldialog.h"
#include "ui_newalgorithmdialog.h"
#include "ui_newfeaturedialog.h"
#include "ui_newdatasetdialog.h"
#include "ui_addsubjectdialog.h"

TestProtocolsController::TestProtocolsController(QObject *parent) :
    QObject(parent){
}


void TestProtocolsController::getInstance(){
    QCOMPARE(ProtocolsController::getInstance(),ProtocolsController::getInstance());
}


void TestProtocolsController::checkProtocolName(){
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
}

void TestProtocolsController::deleteProtocol(){
    ProtocolsController *protocolscontroller = ProtocolsController::getInstance();
}

void TestProtocolsController::associateProtocol(){

    ProtocolsController *protocolscontroller = ProtocolsController::getInstance();

}

void TestProtocolsController::removeProtocolAssociation(){

    ProtocolsController *protocolscontroller = ProtocolsController::getInstance();

}


/*void TestProtocolsController::viewNewProtocolDialog(){
    ProtocolsController *protocolscontroller = ProtocolsController::getInstance();

    protocolscontroller->viewNewProtocolDialog();

    QCOMPARE(protocolscontroller->protocolDialog->result(),1);
}
*/
