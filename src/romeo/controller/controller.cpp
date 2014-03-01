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

Controller* Controller::instance=0;

Controller::Controller(QObject *parent): QObject(parent)
{
    modelCore = ModelCore::getInstance(this);


    algorithmsList = modelCore->getAlgorithmsList();
    featuresList = modelCore->getFeaturesList();
    protocolsList = modelCore->getProtocolsList();
    datasetsList = modelCore->getDatasetsList();

    ////////////PROVA TEST
    QList<AbstractAlgorithm::AlgorithmParameter> param;
    AbstractAlgorithm::AlgorithmParameter param1 (QString("param1"), AbstractAlgorithm::BOOL, QString("default"));
    AbstractAlgorithm::AlgorithmParameter param2 (QString("param2"), AbstractAlgorithm::CHAR, QString("default"));
    param.append(param1);
    param.append(param2);
    AbstractAlgorithm* alg=new UserDefinedAlgorithm(param, QString("Algoritmo1"), QString("desc"), QString("libreria"), QString("nomefunz"));
    algorithmsList->addAlgorithm(alg);

    QList<AbstractAlgorithm::AlgorithmParameter> params;
    AbstractAlgorithm::AlgorithmParameter param11 (QString("Param1"), AbstractAlgorithm::INT, QString("25"));
    AbstractAlgorithm::AlgorithmParameter param22 (QString("Param2"), AbstractAlgorithm::CHAR, QString("default"));
    params.append(param11);
    params.append(param22);
    AbstractAlgorithm* alg2=new UserDefinedAlgorithm(params, QString("Algoritmo"), QString("desc2"), QString("libreria"), QString("nomefunz"));
    algorithmsList->addAlgorithm(alg2);


    AbstractFeature* feat1 = new FirstOrderFeature("FeatureFO1","PATH","PATH","DESC1");
    AbstractFeature* feat2 = new FirstOrderFeature("FeatureFO2","PATH","PATH","DESC2");
    AbstractFeature* feat3 = new DynamicFeature("FeatureD1","PATH","PATH","DESC3");
    AbstractFeature* feat4 = new SecondOrderFeature("FeatureSO1","PATH","PATH","DESC4");
    featuresList->addFeature(feat1);
    featuresList->addFeature(feat2);
    featuresList->addFeature(feat3);
    featuresList->addFeature(feat4);


    QList<AbstractFeature*> features;
    features.append(feat1);
    features.append(feat2);
    features.append(feat4);
    protocolsList->addProtocol("PROVA","descrizione",alg,features,false, STATIC);

    ///////////////PROVA TEST

    mainWindow = new MainWindow();
    protocolDialog = new ProtocolDialog(algorithmsList,featuresList,mainWindow);
    newDatasetDialog = new NewDatasetDialog(mainWindow);
    newAlgorithmDialog = new NewAlgorithmDialog(mainWindow);

    mainWindow->getDatasetPanel()->setCurrentDataset(datasetsList->getFirstDataset());


    newFeatureDialog = new NewFeatureDialog(mainWindow);
    algorithmsListDialog = new AlgorithmsListDialog(algorithmsList,mainWindow);
    featuresListDialog = new FeaturesListDialog(featuresList,mainWindow);

    addSubjectDialog = new AddSubjectDialog(mainWindow);

    protocolsExplorer = mainWindow->getProtocolsExplorer();

    datasetsExplorer = mainWindow->getDatasetsExplorer();

    protocolsExplorer->setProtocolsList(protocolsList);

    datasetsExplorer->setDatasetsList(datasetsList);

    DatasetPanel* datasetPanel = mainWindow->getDatasetPanel();

    protocolsPanel = datasetPanel->getProtocolsPanel();

    executePanel = datasetPanel->getExecutePanel();

    subjectsPanel = datasetPanel->getSubjectsPanel();





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
    mainWindow->getDatasetPanel()->setCurrentDataset(dataset);
}


void Controller::addSubject(QString subjectName, QString dataPath, QString maskPath){
    mainWindow->getDatasetPanel()->getCurrentDataset()->createNewSubject(subjectName,dataPath,maskPath);
}


void Controller::deleteCurrentDataset(){
    AbstractDataset * currentDataset = mainWindow->getDatasetPanel()->getCurrentDataset();
    if(currentDataset != 0){
        datasetsList->deleteDataset(currentDataset);
        currentDataset = datasetsList->getFirstDataset();
        mainWindow->getDatasetPanel()->setCurrentDataset(currentDataset);
    }
}


void Controller::deleteSubject(QString subjectName){
    mainWindow->getDatasetPanel()->getCurrentDataset()->deleteSubject(subjectName);
}


void Controller::deleteProtocol(QString protocolName){
    datasetsList->deleteProtocolAssociations(protocolName);
    protocolsList->removeProtocol(protocolName);
}
