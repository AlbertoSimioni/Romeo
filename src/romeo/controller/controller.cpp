/**
* \file controller.cpp
* \author Matteo Pozza
* \date 2014-02-17
**
* \brief  della classe Controller del package romeo::controller
*/

#include "controller.h"
#include <src/romeo/view/mainWindow/mainwindow.h>
#include <QDebug>
#include <src/romeo/model/inputformats.h>
#include<src/romeo/controller/analysiscontroller.h>
#include<src/romeo/controller/protocolscontroller.h>
#include<src/romeo/controller/abouthelpcontroller.h>
#include<src/romeo/model/core/modelcore.h>

using namespace romeo::controller;
using namespace romeo::view::mainWindow;
using namespace romeo::view;
using namespace romeo::model::core;
using namespace romeo::view::dialogs;

using namespace romeo::model::datasets;
using namespace romeo::model;

DatasetsController* DatasetsController::instance=0;

DatasetsController::DatasetsController(QObject *parent): QObject(parent)
{
    ModelCore::getInstance(this);

    datasetsList = DatasetsList::getInstance();

    mainWindow = new MainWindow();

    AnalysisController::getInstance(mainWindow,this);

    ProtocolsController::getInstance(mainWindow,this);

    AboutHelpController::getInstance(mainWindow,this);

    newDatasetDialog = new NewDatasetDialog(mainWindow);

    addSubjectDialog = new AddSubjectDialog(mainWindow);

    datasetsExplorer = mainWindow->getDatasetsExplorer();

    datasetsExplorer->setDatasetsList(datasetsList);

    DatasetPanel* datasetPanel = mainWindow->getDatasetPanel();

    subjectsPanel = datasetPanel->getSubjectsPanel();

    connectViewsSignals();
    mainWindow->showMaximized();
    QSettings settings;
    QString datasetName = settings.value("lastDataset").toString();
    AbstractDataset* nextDataset = datasetsList->getDataset(datasetName);
    if(!nextDataset)
         nextDataset= datasetsList->getNextDataset(0);
    if(nextDataset)
        changeCurrentDataset(nextDataset->getName());
    else{
        mainWindow->getDatasetPanel()->setCurrentDataset(0);
    }
}

DatasetsController::~DatasetsController(){
    QSettings settings;
    AbstractDataset* currentDataset =mainWindow->getDatasetPanel()->getCurrentDataset();
    if(currentDataset)
        settings.setValue("lastDataset", currentDataset->getName());
    delete mainWindow;

}

void DatasetsController::connectViewsSignals(){
    connect(mainWindow,SIGNAL(openNewDatasetDialog()),this,SLOT(viewNewDatasetDialog()));

    connect(newDatasetDialog,SIGNAL(nameChanged(QString)),this,SLOT(checkDatasetName(QString)));
    connect(newDatasetDialog,SIGNAL(createDataset(QString,romeo::model::InputFormat)),this,SLOT(addDataset(QString,romeo::model::InputFormat)));
    connect(subjectsPanel,SIGNAL(openAddSubjectDialog()),this,SLOT(viewAddSubjectDialog()));
    connect(datasetsExplorer,SIGNAL(currentDatasetChanged(QString)),this,SLOT(changeCurrentDataset(QString)));
    connect(subjectsPanel,SIGNAL(createNewSubject(QString,QString,QString)),this,SLOT(addSubject(QString,QString,QString)));
    connect(mainWindow,SIGNAL(deleteCurrentDataset()),this,SLOT(deleteCurrentDataset()));
    connect(addSubjectDialog,SIGNAL(createNewSubject(QString,QString,QString)),this,SLOT(addSubject(QString,QString,QString)));
    connect(addSubjectDialog,SIGNAL(nameChanged(QString)),this,SLOT(checkSubjectName(QString)));
    connect(subjectsPanel,SIGNAL(deleteSubject(QString)),this,SLOT(deleteSubject(QString)));


}
romeo::view::mainWindow::MainWindow *DatasetsController::getMainWindow() const
{
    return mainWindow;
}


DatasetsController* DatasetsController::getInstance(QObject *parent){
    if(instance == 0){
        instance = new DatasetsController(parent);
    }

    return instance;
}

void DatasetsController::viewNewDatasetDialog(){
    newDatasetDialog->exec();
}


void DatasetsController::viewAddSubjectDialog(){
    addSubjectDialog->exec();
}


void DatasetsController::checkDatasetName(QString datasetName){
    if(datasetsList->getDataset(datasetName)){
        newDatasetDialog->showErrorName(true);
    }
    else{
        newDatasetDialog->showErrorName(false);
    }
}

void DatasetsController::checkSubjectName(QString subjectName){
    if(mainWindow->getDatasetPanel()->getCurrentDataset()->getSubject(subjectName)){
        addSubjectDialog->showErrorName(true);
    }
    else{
        addSubjectDialog->showErrorName(false);
    }
}


void DatasetsController::addDataset(QString name, romeo::model::InputFormat type){
    datasetsList->addDataset(name,type);
}

void DatasetsController::changeCurrentDataset(QString name){
    AbstractDataset* dataset = datasetsList->getDataset(name);

    InputFormat datasetType = dataset->getType();

    ProtocolsController::getInstance()->changeCurrentProtocolsType(dataset->getProtocolsType());
    mainWindow->getFileSystemExplorer()->setCurrentInputFormat(datasetType);
    addSubjectDialog->setCurrentInputFormat(datasetType);
    mainWindow->getDatasetPanel()->setCurrentDataset(dataset);
}


void DatasetsController::addSubject(QString subjectName, QString dataPath, QString maskPath){
    mainWindow->getDatasetPanel()->getCurrentDataset()->createNewSubject(subjectName,dataPath,maskPath);
}


void DatasetsController::deleteCurrentDataset(){
    AbstractDataset * currentDataset = mainWindow->getDatasetPanel()->getCurrentDataset();
    if(currentDataset != 0){
        AbstractDataset* nextDataset = datasetsList->getNextDataset(currentDataset);
        mainWindow->getDatasetPanel()->setCurrentDataset(nextDataset);

        datasetsList->deleteDataset(currentDataset);
    }
    AnalysisController::getInstance()->changeExecuteDialogCurrentDataset(0);
}


void DatasetsController::deleteSubject(QString subjectName){
    mainWindow->getDatasetPanel()->getCurrentDataset()->deleteSubject(subjectName);
}


