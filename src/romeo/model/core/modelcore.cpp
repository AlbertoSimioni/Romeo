#include "modelcore.h"
#include<QMessageBox>
using namespace romeo::model::core;
using namespace romeo::model::imageIO;
using namespace romeo::model::datasets;
using namespace romeo::model::protocols;

ModelCore* ModelCore::instance=0;


ModelCore::ModelCore(QObject *parent): QObject(parent)
{
    writer=Writer::getInstance(this);
    loader=Loader::getInstance(this);
    createLists();
    dataHome=QDir::current();
    if(!dataHome.cd("data"))
    {
        emit ioError(QString("Data directory not found, please make sure a directory named 'data' is in the software folder"));
    }

    //loader->loadFeatures(dataHome.absolutePath().append("/features.xml"), featuresList);
    //loader->loadAlgorithms(dataHome.absolutePath().append("/algorithms.xml"), algorithmsList);
}

void ModelCore::createLists()
{
    datasetsList=DatasetsList::getInstance(this);
    protocolsList=ProtocolsList::getInstance(this);
    algorithmsList=algorithms::AlgorithmsList::getInstance(this);
    featuresList=features::FeaturesList::getInstance(this);

    connect(protocolsList, SIGNAL(protocolsListModified()), writer, SLOT(saveProtocolsList()));
    connect(datasetsList, SIGNAL(datasetsListModified()), writer, SLOT(saveDatasetsList()));
    connect(algorithmsList, SIGNAL(algorithmsListModified()), writer, SLOT(saveAlgorithmsList()));
    connect(featuresList, SIGNAL(featuresListModified()), writer, SLOT(saveFeaturesList()));
    connect(datasetsList, SIGNAL(datasetModified(QString&)), writer, SLOT(saveDataset(QString&)));
}
QDir ModelCore::getDataHome() const
{
    return dataHome;
}

void ModelCore::setDataHome(const QDir &value)
{
    dataHome = value;
}


ModelCore* ModelCore::getInstance(QObject *parent){
    if(instance == 0){
        instance = new ModelCore(parent);
    }
    return instance;
}

DatasetsList* ModelCore::getDatasetsList() const
{
    return datasetsList;
}


features::FeaturesList* ModelCore::getFeaturesList() const
{
    return featuresList;
}

algorithms::AlgorithmsList* ModelCore::getAlgorithmsList() const
{
    return algorithmsList;
}


ProtocolsList* ModelCore::getProtocolsList() const
{
    return protocolsList;
}
