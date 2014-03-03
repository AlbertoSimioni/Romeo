#include "controller.h"
#include <src/romeo/view/mainWindow/mainwindow.h>

/////////PROVA TEST
#include <src/romeo/model/protocols/algorithms/userdefinedalgorithm.h>
#include <src/romeo/model/protocols/features/dynamicfeature.h>
#include <src/romeo/model/protocols/features/firstorderfeature.h>
#include <src/romeo/model/protocols/features/secondorderfeature.h>
#include <src/romeo/model/protocols/abstractprotocol.h>
#include <src/romeo/model/datasets/abstractdataset.h>
#include <QDebug>
#include <src/romeo/model/inputformats.h>
////////PROVA TEST
using namespace romeo::controller;
using namespace romeo::view::mainWindow;
using namespace romeo::view;
using namespace romeo::model::core;
using namespace romeo::view::dialogs;
using namespace romeo::model::protocols::algorithms;
using namespace romeo::model::protocols::features;
using namespace romeo::model::protocols;
using namespace romeo::model::datasets;
using namespace romeo::model;

Controller* Controller::instance=0;

Controller::Controller(QObject *parent): QObject(parent)
{
    modelCore = ModelCore::getInstance(this);
    //modelCore->save();

    algorithmsList = modelCore->getAlgorithmsList();
    featuresList = modelCore->getFeaturesList();
    protocolsList = modelCore->getProtocolsList();
    datasetsList = modelCore->getDatasetsList();


    mainWindow = new MainWindow();

    protocolDialog = new ProtocolDialog(algorithmsList,featuresList,mainWindow);
    newDatasetDialog = new NewDatasetDialog(mainWindow);
    newAlgorithmDialog = new NewAlgorithmDialog(mainWindow);




    newFeatureDialog = new NewFeatureDialog(mainWindow);
    algorithmsListDialog = new AlgorithmsListDialog(algorithmsList,mainWindow);
    featuresListDialog = new FeaturesListDialog(featuresList,mainWindow);

    addSubjectDialog = new AddSubjectDialog(mainWindow);

    associateProtocolDialog = new AssociateProtocolDialog(protocolsList,mainWindow);

    protocolsExplorer = mainWindow->getProtocolsExplorer();

    datasetsExplorer = mainWindow->getDatasetsExplorer();

    protocolsExplorer->setProtocolsList(protocolsList);

    datasetsExplorer->setDatasetsList(datasetsList);

    DatasetPanel* datasetPanel = mainWindow->getDatasetPanel();

    protocolsPanel = datasetPanel->getProtocolsPanel();

    executePanel = datasetPanel->getExecutePanel();

    subjectsPanel = datasetPanel->getSubjectsPanel();



    connectViewsSignals();
    mainWindow->showMaximized();

    AbstractDataset* nextDataset = datasetsList->getNextDataset(0);
    if(nextDataset)
        changeCurrentDataset(nextDataset->getName());
    else{
        mainWindow->getDatasetPanel()->setCurrentDataset(0);
    }
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
    connect(newAlgorithmDialog,SIGNAL(nameChanged(QString)),this,SLOT(checkAlgorithmName(QString)));
    connect(newFeatureDialog,SIGNAL(nameChanged(QString)),this,SLOT(checkFeatureName(QString)));
    connect(newDatasetDialog,SIGNAL(nameChanged(QString)),this,SLOT(checkDatasetName(QString)));
    connect(protocolDialog,SIGNAL(createProtocol(QString,QString,bool,QList<QString>,QString,romeo::model::protocols::ProtocolType,int,int)),this,SLOT(addProtocol(QString,QString,bool,QList<QString>,QString,romeo::model::protocols::ProtocolType,int,int)));
    connect(newAlgorithmDialog,SIGNAL(createAlgorithm(QString,QString,QString,QString,QList<romeo::model::protocols::algorithms::AbstractAlgorithm::AlgorithmParameter>)),this,SLOT(addAlgorithm(QString,QString,QString,QString,QList<romeo::model::protocols::algorithms::AbstractAlgorithm::AlgorithmParameter>)));
    connect(newFeatureDialog,SIGNAL(createFeature(QString,QString,QString,QString,romeo::model::protocols::features::FeatureType)),this,SLOT(addFeature(QString,QString,QString,QString,romeo::model::protocols::features::FeatureType)));
    connect(newDatasetDialog,SIGNAL(createDataset(QString,romeo::model::InputFormat)),this,SLOT(addDataset(QString,romeo::model::InputFormat)));
    connect(subjectsPanel,SIGNAL(openAddSubjectDialog()),this,SLOT(viewAddSubjectDialog()));
    connect(datasetsExplorer,SIGNAL(currentDatasetChanged(QString)),this,SLOT(changeCurrentDataset(QString)));
    connect(subjectsPanel,SIGNAL(createNewSubject(QString,QString,QString)),this,SLOT(addSubject(QString,QString,QString)));
    connect(mainWindow,SIGNAL(deleteCurrentDataset()),this,SLOT(deleteCurrentDataset()));
    connect(addSubjectDialog,SIGNAL(createNewSubject(QString,QString,QString)),this,SLOT(addSubject(QString,QString,QString)));
    connect(addSubjectDialog,SIGNAL(nameChanged(QString)),this,SLOT(checkSubjectName(QString)));
    connect(subjectsPanel,SIGNAL(deleteSubject(QString)),this,SLOT(deleteSubject(QString)));
    connect(mainWindow,SIGNAL(deleteProtocol(QString)),this,SLOT(deleteProtocol(QString)));
    connect(protocolsPanel,SIGNAL(associateProtocol(QString)),this,SLOT(associateProtocol(QString)));
    connect(protocolsPanel,SIGNAL(openAssociateProtocolDialog()),this,SLOT(viewAssociateProtocolDialog()));
    connect(associateProtocolDialog,SIGNAL(associateProtocol(QString)),this,SLOT(associateProtocol(QString)));
    connect(protocolsPanel,SIGNAL(removeProtocolAssociation(QString)),this,SLOT(removeProtocolAssociation(QString)));
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

void Controller::viewAddSubjectDialog(){
    addSubjectDialog->exec();
}


void Controller::viewAssociateProtocolDialog(){
    associateProtocolDialog->exec();
}

void Controller::checkProtocolName(QString protocolName){
    if(protocolsList->getProtocol(protocolName)){
        protocolDialog->showErrorName(true);
    }
    else{
        protocolDialog->showErrorName(false);
    }
}


void Controller::checkAlgorithmName(QString algorithmName){
    if(algorithmsList->getAlgorithm(algorithmName)){
        newAlgorithmDialog->showErrorName(true);
    }
    else{
        newAlgorithmDialog->showErrorName(false);
    }
}


void Controller::checkFeatureName(QString featureName){
    if(featuresList->getFeature(featureName)){
            newFeatureDialog->showErrorName(true);
    }
    else{
        newFeatureDialog->showErrorName(false);
    }
}

void Controller::checkDatasetName(QString datasetName){
    if(datasetsList->getDataset(datasetName)){
        newDatasetDialog->showErrorName(true);
    }
    else{
        newDatasetDialog->showErrorName(false);
    }
}

void Controller::checkSubjectName(QString subjectName){
    if(mainWindow->getDatasetPanel()->getCurrentDataset()->getSubject(subjectName)){
        addSubjectDialog->showErrorName(true);
    }
    else{
        addSubjectDialog->showErrorName(false);
    }
}

void Controller::addProtocol(QString protocolName, QString desc, bool test, QList<QString> features, QString algorithm, ProtocolType type, int windowSize, int distanceGLCM){
    AbstractAlgorithm* associatedAlgorithm = algorithmsList->getAlgorithm(algorithm);
    QList<AbstractFeature*> associatedFeatures;
    for(int i = 0; i<features.size();i++){
        associatedFeatures.append(featuresList->getFeature(features[i]));
    }

    protocolsList->addProtocol(protocolName,desc,associatedAlgorithm,associatedFeatures,test,type,windowSize,distanceGLCM);
}

void Controller::addAlgorithm(QString name, QString desc, QString dyfn, QString dylp, QList<AbstractAlgorithm::AlgorithmParameter> parameters){
    algorithmsList->addAlgorithm(name,desc,parameters,dylp,dyfn);
}


void Controller::addFeature(QString name, QString desc, QString dyfn, QString dylp, FeatureType type){
    featuresList->addFeature(name,type,desc,dylp,dyfn);
}

void Controller::addDataset(QString name, romeo::model::InputFormat type){
    datasetsList->addDataset(name,type);
}

void Controller::changeCurrentDataset(QString name){


    AbstractDataset* dataset = datasetsList->getDataset(name);

    InputFormat datasetType = dataset->getType();

    protocolsExplorer->setCurrentProtocolsType(dataset->getProtocolsType());
    associateProtocolDialog->setCurrentProtocolsType(dataset->getProtocolsType());
    mainWindow->getFileSystemExplorer()->setCurrentInputFormat(datasetType);
    addSubjectDialog->setCurrentInputFormat(datasetType);
    mainWindow->getDatasetPanel()->setCurrentDataset(dataset);
}


void Controller::addSubject(QString subjectName, QString dataPath, QString maskPath){
    mainWindow->getDatasetPanel()->getCurrentDataset()->createNewSubject(subjectName,dataPath,maskPath);
}


void Controller::deleteCurrentDataset(){
    AbstractDataset * currentDataset = mainWindow->getDatasetPanel()->getCurrentDataset();
    if(currentDataset != 0){
        AbstractDataset* nextDataset = datasetsList->getNextDataset(currentDataset);
        mainWindow->getDatasetPanel()->setCurrentDataset(nextDataset);
        datasetsList->deleteDataset(currentDataset);
        //changeCurrentDataset(currentDataset->getName());
    }
}


void Controller::deleteSubject(QString subjectName){
    mainWindow->getDatasetPanel()->getCurrentDataset()->deleteSubject(subjectName);
}


void Controller::deleteProtocol(QString protocolName){
    datasetsList->deleteProtocolAssociations(protocolName);
    protocolsList->removeProtocol(protocolName);
}

void Controller::associateProtocol(QString protocolName){
    AbstractDataset* currentDataset = mainWindow->getDatasetPanel()->getCurrentDataset();
    AbstractProtocol* alreadyPresent = currentDataset->getProtocol(protocolName);
    if(!alreadyPresent){
        AbstractProtocol* protocol = protocolsList->getProtocol(protocolName);
        currentDataset->associateProtocol(protocol);
    }

}


void Controller::removeProtocolAssociation(QString protocolName){

    AbstractDataset* currentDataset = mainWindow->getDatasetPanel()->getCurrentDataset();
    currentDataset->removeProtocolAssociation(protocolName);

}
