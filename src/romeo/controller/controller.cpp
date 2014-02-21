#include "controller.h"
#include <src/romeo/view/mainWindow/mainwindow.h>
using namespace romeo::controller;
using namespace romeo::view::mainWindow;
using namespace romeo::view;

Controller* Controller::instance=0;

Controller::Controller(QObject *parent): QObject(parent)
{
    viewManager = ViewManager::getInstance(this);
    connectViewsSignals();
}


void Controller::connectViewsSignals(){
    connect(viewManager->getMainWindow(),SIGNAL(openNewDatasetDialog()),this,SLOT(viewNewDatasetDialog()));
    connect(viewManager->getMainWindow(),SIGNAL(openNewPortocolDialog()),this,SLOT(viewNewProtocolDialog()));
    connect(viewManager->getMainWindow(),SIGNAL(openNewAlgorithmDialog()),this,SLOT(viewNewAlgorithmDialog()));
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

}
