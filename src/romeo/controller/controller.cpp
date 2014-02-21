#include "controller.h"
#include <src/romeo/view/mainWindow/mainwindow.h>
using namespace romeo::controller;
using namespace romeo::view::mainWindow;
using namespace romeo::view;
using namespace romeo::model::core;

Controller* Controller::instance=0;

Controller::Controller(QObject *parent): QObject(parent)
{
    modelCore = ModelCore::getInstance(this);
    viewManager = ViewManager::getInstance(this);
    connectViewsSignals();
}


void Controller::connectViewsSignals(){
    connect(viewManager->getMainWindow(),SIGNAL(openNewDatasetDialog()),this,SLOT(viewNewDatasetDialog()));
    connect(viewManager->getMainWindow(),SIGNAL(openNewPortocolDialog()),this,SLOT(viewNewProtocolDialog()));
    connect(viewManager->getMainWindow(),SIGNAL(openNewAlgorithmDialog()),this,SLOT(viewNewAlgorithmDialog()));
    connect(viewManager->getMainWindow(),SIGNAL(openAlgorithmsListDialog()),this,SLOT(viewAlgorithmsListDialog()));
    connect(viewManager->getMainWindow(),SIGNAL(openFeaturesListDialog()),this,SLOT(viewFeaturesListDialog()));
    connect(viewManager->getMainWindow(),SIGNAL(openNewFeatureDialog()),this,SLOT(viewNewFeatureDialog()));
    connect(viewManager->getProtocolDialog(),SIGNAL(nameChanged(QString)),this,SLOT(checkProtocolName(QString)));
}

Controller* Controller::getInstance(QObject *parent){
    if(instance == 0){
        instance = new Controller(parent);
    }

    return instance;
}

void Controller::viewNewDatasetDialog(){
    viewManager->showNewDataset();
}

void Controller::viewNewProtocolDialog(){
    viewManager->showNewProtocol();
}


void Controller::viewNewAlgorithmDialog(){
    viewManager->showNewAlgorithm();
}


void Controller::viewNewFeatureDialog(){
    viewManager->showNewFeature();
}


void Controller::viewAlgorithmsListDialog(){
    viewManager->showAlgorithmsList();
}

void Controller::viewFeaturesListDialog(){
    viewManager->showFeaturesList();
}


void Controller::checkProtocolName(QString protocolName){
  /*  if(!(modelCore->getProtocolsList()->getProtocol(protocolName))){
        viewManager->getProtocolDialog()->showErrorName(true);
    }
    else{
        viewManager->getProtocolDialog()->showErrorName(false);
    } da decommentare quando satà pronto il getprotocol*/
}
