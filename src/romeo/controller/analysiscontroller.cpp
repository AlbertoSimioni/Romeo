/**
* \file analysiscontroller.cpp
* \author Matteo Pozza
* \date 2014-02-17
**
* \brief Header della classe AnalysisController del package romeo::controller
*/

#include "analysiscontroller.h"
#include<QCoreApplication>

using namespace romeo::controller;
using namespace romeo::model::datasets;
using namespace romeo::model::protocols;
using namespace romeo::view::dialogs;


AnalysisController* AnalysisController::instance=0;


AnalysisController::AnalysisController(view::mainWindow::MainWindow* mainw, QObject *parent) : mainWindow(mainw),
    analysisThread(0),QObject(parent)
{

    executeDialog = new ExecuteDialog(mainWindow);
    connectViewsSignals();
}


AnalysisController* AnalysisController::getInstance(view::mainWindow::MainWindow* mainw,QObject *parent){
    if(instance == 0){
        instance = new AnalysisController(mainw,parent);
    }

    return instance;
}


void AnalysisController::connectViewsSignals(){

    connect(executeDialog,SIGNAL(abortAnalysis()),this,SLOT(abortAnalysis()));
    connect(mainWindow->getDatasetPanel(),SIGNAL(executeAnalysis(QString,QList<QString>,QString,bool,bool,bool,QString)),this,SLOT(startAnalysis(QString,QList<QString>,QString,bool,bool,bool,QString)));
    connect(executeDialog,SIGNAL(forceAbortAnalysis()),this,SLOT(forceAbortAnalysis()));
}


void AnalysisController::startAnalysis(QString protocol, QList<QString> subjects, QString resultsPath, bool viewResults, bool viewFeatures, bool saveFeatures, QString format)
{
    AbstractDataset* currentDataset = mainWindow->getDatasetPanel()->getCurrentDataset();
    AbstractProtocol* prot = ProtocolsList::getInstance()->getProtocol(protocol);
    int nAlgorithm = 0;
    if(prot->getAlgorithm()){
        ++nAlgorithm;
    }
    executeDialog->prepareAnalysis(currentDataset,viewResults,viewFeatures,subjects.size(),nAlgorithm,prot->getFeatures().size());
    analysisThread = new AnalysisThread(this,this);
    analysisThread->prepareAnalysis(protocol,subjects,resultsPath,saveFeatures,format);
    analysisThread->start();
    executeDialog->exec();
}

void AnalysisController::AnalysisThread::prepareAnalysis(QString prot, QList<QString> subs, QString resPath, bool saveFeats, QString exportFormat){
    protocol = prot;
    subjects = subs;
    resultsPath = resPath;
    saveFeatures = saveFeats;
    format = exportFormat;
}

void AnalysisController::AnalysisThread::run(){

    AbstractDataset* currentDataset = analysisController->mainWindow->getDatasetPanel()->getCurrentDataset();
    currentDataset->executeAnalysis(protocol,subjects,resultsPath,saveFeatures,format);
}


AnalysisController::AnalysisThread::AnalysisThread(AnalysisController *controller,QObject* parent):
    analysisController(controller), QThread(parent)
{
    setTerminationEnabled(true);
}

void AnalysisController::abortAnalysis(){
    mainWindow->getDatasetPanel()->getCurrentDataset()->abortAnalysis();
}


void AnalysisController::changeExecuteDialogCurrentDataset(romeo::model::datasets::AbstractDataset *currDataset){
    executeDialog->setCurrentDataset(currDataset);
}


void AnalysisController::forceAbortAnalysis(){
    analysisThread->exit(0);
    analysisThread->terminate();

}



