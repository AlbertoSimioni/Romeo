#include "modelcore.h"
using namespace romeo::model::core;
using namespace romeo::model::imageIO;
using namespace romeo::model::datasets;
using namespace romeo::model::protocols;

ModelCore* ModelCore::instance=0;


ModelCore::ModelCore(QObject *parent): QObject(parent)
{
    writer=Writer::getInstance();
    loader=Loader::getInstance();
    createLists();

   //loader->loadDatabase(databaseFile, datasetsFiles, datasetsList);
    //for(QHash::Iterator it=datasetsFiles.begin(); it != datasetsFiles.end(); ++it)
    {

    }
}

void ModelCore::createLists()
{
    datasetsList=DatasetsList::getInstance();
    protocolsList=new ProtocolsList();
    algorithmsList=new algorithms::AlgorithmsList();
    featuresList=new features::FeaturesList();


    connect(protocolsList, SIGNAL(protocolsListModified()), this, SLOT(saveProtocolsList()));
    connect(datasetsList, SIGNAL(datasetsListModified()), this, SLOT(saveDatasetsList()));
    connect(algorithmsList, SIGNAL(algorithmsListModified()), this, SLOT(saveAlgorithmsList()));
    connect(featuresList, SIGNAL(featuresListModified()), this, SLOT(saveFeaturesList()));
    connect(datasetsList, SIGNAL(datasetModified(QString&)), this, SLOT(saveDataset(QString&)));
}

bool ModelCore::saveDatasetsList()
{
    return true;
}

bool ModelCore::saveProtocolsList()
{
    //writer->writeProtocols(QDir());
}

bool ModelCore::saveAlgorithmsList()
{
    //writer->writeAlgorithms(QDir());
}

bool ModelCore::saveFeaturesList()
{
    return true;
}

bool ModelCore::saveDataset(QString &datasetName)
{
    return true;
}
ModelCore* ModelCore::getInstance(QObject *parent){
    if(instance == 0){
        instance = new ModelCore(parent);
    }
    return instance;
}

DatasetsList *ModelCore::getDatasetsList() const
{
    return datasetsList;
}


features::FeaturesList *ModelCore::getFeaturesList() const
{
    return featuresList;
}

algorithms::AlgorithmsList *ModelCore::getAlgorithmsList() const
{
    return algorithmsList;
}


ProtocolsList *ModelCore::getProtocolsList() const
{
    return protocolsList;
}
