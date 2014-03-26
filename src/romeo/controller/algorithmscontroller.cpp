/**
* \file algorithmscontroller.h
* \author Matteo Pozza
* \date 2014-02-17
**
* \brief Header della classe AlgorithmsController del package romeo::controller
*/
#include "algorithmscontroller.h"


using namespace romeo::controller;
using namespace romeo::model::protocols::algorithms;
using namespace romeo::view::dialogs;

AlgorithmsController* AlgorithmsController::instance=0;

AlgorithmsController::AlgorithmsController(romeo::view::mainWindow::MainWindow* mainw ,QObject *parent) :
    mainWindow(mainw),QObject(parent)
{
     algorithmsList = AlgorithmsList::getInstance();
     algorithmsListDialog = new AlgorithmsListDialog(algorithmsList,mainWindow);
     newAlgorithmDialog = new NewAlgorithmDialog(mainWindow);
     connectViewsSignals();


}

AlgorithmsController* AlgorithmsController::getInstance(view::mainWindow::MainWindow* mainw,QObject *parent){
    if(instance == 0){
        instance = new AlgorithmsController(mainw,parent);
    }

    return instance;
}


void AlgorithmsController::connectViewsSignals(){
   connect(newAlgorithmDialog,SIGNAL(nameChanged(QString)),this,SLOT(checkAlgorithmName(QString)));
   connect(newAlgorithmDialog,SIGNAL(createAlgorithm(QString,QString,QString,QString,QList<romeo::model::protocols::algorithms::AbstractAlgorithm::AlgorithmParameter>)),this,SLOT(addAlgorithm(QString,QString,QString,QString,QList<romeo::model::protocols::algorithms::AbstractAlgorithm::AlgorithmParameter>)));
   connect(mainWindow,SIGNAL(openNewAlgorithmDialog()),this,SLOT(viewNewAlgorithmDialog()));
   connect(mainWindow,SIGNAL(openAlgorithmsListDialog()),this,SLOT(viewAlgorithmsListDialog()));

}



void AlgorithmsController::viewAlgorithmsListDialog(){
    algorithmsListDialog->exec();
}

void AlgorithmsController::viewNewAlgorithmDialog(){
    newAlgorithmDialog->exec();
}



void AlgorithmsController::checkAlgorithmName(QString algorithmName){
    if(algorithmsList->getAlgorithm(algorithmName)){
        newAlgorithmDialog->showErrorName(true);
    }
    else{
        newAlgorithmDialog->showErrorName(false);
    }
}


void AlgorithmsController::addAlgorithm(QString name, QString desc, QString dyfn, QString dylp, QList<AbstractAlgorithm::AlgorithmParameter> parameters){
    algorithmsList->addAlgorithm(name,desc,parameters,dylp,dyfn);
}



