#include "modelcore.h"

using namespace romeo::model::core;
using namespace romeo::model::imageIO;
using namespace romeo::model::datasets;
using namespace romeo::model::protocols;

ModelCore* ModelCore::instance=0;

ModelCore::ModelCore(QObject *parent): QObject(parent)
{
    writer=Writer::getInstance(this);
    loader=Loader::getInstance(this);
    dataHome=QDir::current();
    if(!dataHome.cd("data"))
    {
        qDebug("non ho caricato");
    }
    createLists();

    writer->saveDatasetsList(dataHome.absolutePath().append("/dat.xml"));

    connect(protocolsList, SIGNAL(protocolsListModified()), writer, SLOT(saveProtocolsList()));
    //connect(datasetsList, SIGNAL(datasetsListModified()), writer, SLOT(saveDatasetsList()), Qt::QueuedConnection);
    connect(algorithmsList, SIGNAL(algorithmsListModified()), writer, SLOT(saveAlgorithmsList()));
    connect(featuresList, SIGNAL(featuresListModified()), writer, SLOT(saveFeaturesList()));
    connect(datasetsList, SIGNAL(datasetModified(QString&)), writer, SLOT(saveDataset(QString&)));

}

void ModelCore::createLists()
{
    datasetsList=DatasetsList::getInstance(this);
    protocolsList=ProtocolsList::getInstance(this);
    algorithmsList=algorithms::AlgorithmsList::getInstance(this);
    featuresList=features::FeaturesList::getInstance(this);

    loader->loadFeatures(dataHome.absolutePath().append("/features.xml"), featuresList);
    loader->loadAlgorithms(dataHome.absolutePath().append("/algorithms.xml"), algorithmsList);
    loader->loadProtocols(dataHome.absolutePath().append("/protocols.xml"), protocolsList);
    loader->loadDatasetsNames(dataHome.absolutePath().append("/datasets.xml"));

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
