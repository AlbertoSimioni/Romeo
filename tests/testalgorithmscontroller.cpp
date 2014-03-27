#include "testalgorithmscontroller.h"
#include "ui_newalgorithmdialog.h"

TestAlgorithmsController::TestAlgorithmsController(QObject *parent) :
    QObject(parent){
}


void TestAlgorithmsController::getInstance(){
    QCOMPARE(AlgorithmsController::getInstance(),AlgorithmsController::getInstance());
}


void TestAlgorithmsController::checkAlgorithmName(){
    AlgorithmsController *algorithmscontroller = AlgorithmsController::getInstance();

    algorithmscontroller->checkAlgorithmName(QString("notExists"));
    QCOMPARE(algorithmscontroller->newAlgorithmDialog->ui->errorLabel->isHidden(),true);

    QString algName = "algName2";
    QString algDescr = "algDescription";
    QList<algorithms::AbstractAlgorithm::AlgorithmParameter> paramList;
    QList<QString> algParameters;
    int clusterNum = 1;
    QString algDylp = "dylp";
    QString algDyfn = "dyfn";
    UserDefinedAlgorithm *myAlg = new UserDefinedAlgorithm(paramList,algName,algDescr,algDylp,algDyfn);

    AlgorithmsList *algList = AlgorithmsList::getInstance();

    algList->addAlgorithm(myAlg);

    algorithmscontroller->checkAlgorithmName(algName);
    QCOMPARE(algorithmscontroller->newAlgorithmDialog->ui->okCancel->button(QDialogButtonBox::Ok)->isEnabled(),false);

    delete myAlg;
}


void TestAlgorithmsController::addAlgorithm(){

    AlgorithmsController *algorithmscontroller = AlgorithmsController::getInstance();

    QString algName = "algName4";
    QString algDescr = "algDescription";
    QList<algorithms::AbstractAlgorithm::AlgorithmParameter> paramList;
    QList<QString> algParameters;
    int clusterNum = 1;
    QString algDylp = "dylp";
    QString algDyfn = "dyfn";

    AlgorithmsList *algList = AlgorithmsList::getInstance();

    algorithmscontroller->addAlgorithm(algName,algDescr,algDyfn,algDylp,paramList);

    QCOMPARE(algList->getAlgorithm(algName)->getName(),algName);

}
