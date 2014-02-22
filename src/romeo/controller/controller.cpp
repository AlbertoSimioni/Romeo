#include "controller.h"
#include <src/romeo/view/mainWindow/mainwindow.h>

/////////PROVA TEST
#include <src/romeo/model/protocols/algorithms/userdefinedalgorithm.h>
////////PROVA TEST
using namespace romeo::controller;
using namespace romeo::view::mainWindow;
using namespace romeo::view;
using namespace romeo::model::core;
using namespace romeo::view::dialogs;
using namespace romeo::model::protocols::algorithms;
Controller* Controller::instance=0;

Controller::Controller(QObject *parent): QObject(parent)
{
    modelCore = ModelCore::getInstance(this);


    algorithmsList = modelCore->getAlgorithmsList();
    featuresList = modelCore->getFeaturesList();

    ////////////PROVA TEST
    QList<AbstractAlgorithm::AlgorithmParameter> param;
    AbstractAlgorithm::AlgorithmParameter param1 (QString("param"), AbstractAlgorithm::BOOL, QString("default"));
    AbstractAlgorithm::AlgorithmParameter param2 (QString("param"), AbstractAlgorithm::CHAR, QString("default"));
    param.append(param1);
    param.append(param2);
    AbstractAlgorithm* alg=new UserDefinedAlgorithm(param, QString("nome alg"), QString("desc"), QString("libreria"), QString("nomefunz"));
    algorithmsList->addAlgorithm(alg);

    QList<AbstractAlgorithm::AlgorithmParameter> params;
    AbstractAlgorithm::AlgorithmParameter param11 (QString("pllolol"), AbstractAlgorithm::INT, QString("fuck"));
    AbstractAlgorithm::AlgorithmParameter param22 (QString("ahaha"), AbstractAlgorithm::CHAR, QString("default"));
    params.append(param11);
    params.append(param22);
    AbstractAlgorithm* alg2=new UserDefinedAlgorithm(params, QString("nome alg2"), QString("desc"), QString("libreria"), QString("nomefunz"));
    algorithmsList->addAlgorithm(alg2);
    ///////////////PROVA TEST

    mainWindow = new MainWindow();
    protocolDialog = new ProtocolDialog(algorithmsList,featuresList,mainWindow);
    newDatasetDialog = new NewDatasetDialog(mainWindow);
    newAlgorithmDialog = new NewAlgorithmDialog(mainWindow);


    newFeatureDialog = new NewFeatureDialog(mainWindow);
    algorithmsListDialog = new AlgorithmsListDialog(mainWindow);
    featuresListDialog = new FeaturesListDialog(mainWindow);


    connectViewsSignals();
    mainWindow->show();
}

Controller::~Controller(){
    delete mainWindow;
}

void Controller::connectViewsSignals(){
    connect(mainWindow,SIGNAL(openNewDatasetDialog()),this,SLOT(viewNewDatasetDialog()));
    connect(mainWindow,SIGNAL(openNewPortocolDialog()),this,SLOT(viewNewProtocolDialog()));
    connect(mainWindow,SIGNAL(openNewAlgorithmDialog()),this,SLOT(viewNewAlgorithmDialog()));
    connect(mainWindow,SIGNAL(openAlgorithmsListDialog()),this,SLOT(viewAlgorithmsListDialog()));
    connect(mainWindow,SIGNAL(openFeaturesListDialog()),this,SLOT(viewFeaturesListDialog()));
    connect(mainWindow,SIGNAL(openNewFeatureDialog()),this,SLOT(viewNewFeatureDialog()));
    connect(protocolDialog,SIGNAL(nameChanged(QString)),this,SLOT(checkProtocolName(QString)));
}

Controller* Controller::getInstance(QObject *parent){
    if(instance == 0){
        instance = new Controller(parent);
    }

    return instance;
}

void Controller::viewNewDatasetDialog(){
    newDatasetDialog->exec();
}

void Controller::viewNewProtocolDialog(){
    protocolDialog->exec();
}


void Controller::viewNewAlgorithmDialog(){
    newAlgorithmDialog->exec();
}


void Controller::viewNewFeatureDialog(){
    newFeatureDialog->exec();
}


void Controller::viewAlgorithmsListDialog(){
    algorithmsListDialog->exec();
}

void Controller::viewFeaturesListDialog(){
    featuresListDialog->exec();
}


void Controller::checkProtocolName(QString protocolName){
  /*  if(!(modelCore->getProtocolsList()->getProtocol(protocolName))){
        viewManager->getProtocolDialog()->showErrorName(true);
    }
    else{
        viewManager->getProtocolDialog()->showErrorName(false);
    } da decommentare quando satà pronto il getprotocol*/
}
