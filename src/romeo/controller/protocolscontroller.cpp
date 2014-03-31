#include "protocolscontroller.h"

#include <src/romeo/model/datasets/datasetslist.h>

using namespace romeo::controller;
using namespace romeo::model::protocols::algorithms;
using namespace romeo::model::protocols::features;
using namespace romeo::model::protocols;
using namespace romeo::view::dialogs;
using namespace romeo::view::mainWindow;
using namespace romeo::model::datasets;
ProtocolsController* ProtocolsController::instance=0;

ProtocolsController::ProtocolsController(view::mainWindow::MainWindow *mainw, QObject *parent) :
    QObject(parent), mainWindow(mainw)
{
    algorithmsList = AlgorithmsList::getInstance();
    featuresList = FeaturesList::getInstance();
    protocolsList = ProtocolsList::getInstance();
    protocolDialog = new ProtocolDialog(algorithmsList,featuresList,mainWindow);
    associateProtocolDialog = new AssociateProtocolDialog(protocolsList,mainWindow);
    protocolsExplorer = mainWindow->getProtocolsExplorer();

    protocolsExplorer->setProtocolsList(protocolsList);
    protocolsPanel = mainWindow->getDatasetPanel()->getProtocolsPanel();

    AlgorithmsController::getInstance(mainWindow,this);
    FeaturesController::getInstance(mainWindow,this);


    connectViewsSignals();
}

ProtocolsController* ProtocolsController::getInstance(view::mainWindow::MainWindow *mainw,QObject *parent){
    if(instance == 0){
        instance = new ProtocolsController(mainw,parent);
    }

    return instance;
}


void ProtocolsController::connectViewsSignals(){

    connect(mainWindow,SIGNAL(openNewPortocolDialog()),this,SLOT(viewNewProtocolDialog()));
    connect(protocolDialog,SIGNAL(nameChanged(QString)),this,SLOT(checkProtocolName(QString)));

    connect(protocolDialog,SIGNAL(createProtocol(QString,QString,bool,QList<QString>,QString,romeo::model::protocols::ProtocolType,int,int,int,int,int,QList<QString>)),this,SLOT(addProtocol(QString,QString,bool,QList<QString>,QString,romeo::model::protocols::ProtocolType,int,int,int,int,int,QList<QString>)));
    connect(protocolDialog,SIGNAL(modifyProtocol(QString,QString,QString,bool,QList<QString>,QString,romeo::model::protocols::ProtocolType,int,int,int,int,int,QList<QString>)),this,SLOT(modifyProtocol(QString,QString,QString,bool,QList<QString>,QString,romeo::model::protocols::ProtocolType,int,int,int,int,int,QList<QString>)));
    connect(mainWindow,SIGNAL(deleteProtocol(QString)),this,SLOT(deleteProtocol(QString)));
    connect(associateProtocolDialog,SIGNAL(associateProtocol(QString)),this,SLOT(associateProtocol(QString)));
    connect(protocolsPanel,SIGNAL(associateProtocol(QString)),this,SLOT(associateProtocol(QString)));
    connect(protocolsPanel,SIGNAL(removeProtocolAssociation(QString)),this,SLOT(removeProtocolAssociation(QString)));
    connect(protocolsPanel,SIGNAL(openAssociateProtocolDialog()),this,SLOT(viewAssociateProtocolDialog()));
    connect(protocolsExplorer,SIGNAL(associateProtocol(QString)),this,SLOT(associateProtocol(QString)));
    connect(protocolsExplorer,SIGNAL(deleteProtocol(QString)),this,SLOT(deleteProtocol(QString)));
    connect(protocolsExplorer,SIGNAL(openProtocol(QString)),this,SLOT(openProtocol(QString)));
}

void ProtocolsController::viewNewProtocolDialog(){
    protocolDialog->exec();
}


void ProtocolsController::viewAssociateProtocolDialog(){
    associateProtocolDialog->exec();
}


void ProtocolsController::checkProtocolName(QString protocolName){
    if(protocolsList->getProtocol(protocolName)){
        protocolDialog->showErrorName(true);
    }
    else{
        protocolDialog->showErrorName(false);
    }
}

void ProtocolsController::addProtocol(QString protocolName, QString desc, bool test, QList<QString> features, QString algorithm, ProtocolType type, int windowSize, int distanceGLCM,int nClusters, int frameInit, int frameEnd, QList<QString> parametersValue){
    AbstractAlgorithm* associatedAlgorithm = algorithmsList->getAlgorithm(algorithm);
    QList<AbstractFeature*> associatedFeatures;
    for(int i = 0; i<features.size();i++){
        associatedFeatures.append(featuresList->getFeature(features[i]));
    }

    protocolsList->addProtocol(protocolName,desc,associatedAlgorithm,nClusters,parametersValue,associatedFeatures,test,type,frameInit,frameEnd,windowSize,distanceGLCM);
}


void ProtocolsController::deleteProtocol(QString protocolName){
    DatasetsList::getInstance()->deleteProtocolAssociations(protocolName);
    protocolsList->removeProtocol(protocolName);
}

void ProtocolsController::associateProtocol(QString protocolName){
    AbstractDataset* currentDataset = mainWindow->getDatasetPanel()->getCurrentDataset();
    AbstractProtocol* alreadyPresent = currentDataset->getProtocol(protocolName);
    if(!alreadyPresent){
        AbstractProtocol* protocol = protocolsList->getProtocol(protocolName);
        currentDataset->associateProtocol(protocol);
    }
}


void ProtocolsController::removeProtocolAssociation(QString protocolName){

    AbstractDataset* currentDataset = mainWindow->getDatasetPanel()->getCurrentDataset();
    currentDataset->removeProtocolAssociation(protocolName);

}


void ProtocolsController::openProtocol(QString protocolName){
    AbstractProtocol * protocol = protocolsList->getProtocol(protocolName);
    if(protocol){
        protocolDialog->openExistingProtocol(protocol);
    }
    protocolDialog->exec();
}


void ProtocolsController::modifyProtocol(QString oldProtocolName, QString protocolName, QString desc, bool test, QList<QString> features, QString algorithm, ProtocolType type, int windowSize, int distanceGLCM, int nClusters, int frameInit, int frameEnd, QList<QString> parametersValue){

    deleteProtocol(oldProtocolName);

    addProtocol(protocolName,desc,test,features,algorithm,type,windowSize,distanceGLCM,nClusters,frameInit,frameEnd,parametersValue);
}


void ProtocolsController::changeCurrentProtocolsType(ProtocolType type){
    protocolsExplorer->setCurrentProtocolsType(type);
    associateProtocolDialog->setCurrentProtocolsType(type);
}
