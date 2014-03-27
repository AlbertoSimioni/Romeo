/**
* \file modelcore.cpp
* \author Matteo Pozza
* \date 2014-02-17
**
* \brief Header della classe ModelCore del package romeo::model::core
*/

#include "modelcore.h"
using namespace romeo::model::core;
using namespace romeo::model::imageIO;
using namespace romeo::model::datasets;
using namespace romeo::model::protocols;
#include <src/romeo/model/protocols/algorithms/kmeans.h>
#include <src/romeo/model/protocols/algorithms/hierarchical.h>
#include <src/romeo/model/protocols/algorithms/fuzzycmeans.h>
/////////PROVA TEST
#include <src/romeo/model/protocols/algorithms/userdefinedalgorithm.h>
#include <src/romeo/model/protocols/features/dynamicfeature.h>
#include <src/romeo/model/protocols/features/firstorderfeature.h>
#include <src/romeo/model/protocols/features/secondorderfeature.h>
#include <src/romeo/model/protocols/abstractprotocol.h>
#include <src/romeo/model/datasets/abstractdataset.h>
#include <QDebug>
#include <src/romeo/model/inputformats.h>
#include <QDate>
using namespace romeo::model::protocols::algorithms;
using namespace romeo::model::protocols::features;
////////PROVA TEST
///


ModelCore* ModelCore::instance=0;
QDir ModelCore::dataHome=QDir::current();
ModelCore::ModelCore(QObject *parent): QObject(parent)
{
    writer=Writer::getInstance(this);
    loader=Loader::getInstance(this);
    dataHome=QDir::current();
    if(!dataHome.cd("data"))
    {
        dataHome.mkdir("data");
        dataHome.cd("data");
    }
    createLists();

    QList<AbstractAlgorithm::AlgorithmParameter> param;
    AbstractAlgorithm::AlgorithmParameter param1 (QString("Distance"), AbstractAlgorithm::CHAR, QString("e"));
    AbstractAlgorithm::AlgorithmParameter param2 (QString("Number of iterations"), AbstractAlgorithm::INT, QString("200"));
    param.append(param1);
    param.append(param2);
    AbstractAlgorithm* alg=KMeans::getInstance(param, QString("K-means"), QString("Partitioning clustering method, exclusive (hard) assignment"));
    AlgorithmsList::getInstance()->addAlgorithm(alg);

    QList<AbstractAlgorithm::AlgorithmParameter> paramh;
    AbstractAlgorithm::AlgorithmParameter paramh1 (QString("Distance"), AbstractAlgorithm::CHAR, QString("e"));
    AbstractAlgorithm::AlgorithmParameter paramh2 (QString("Linkage criteria"), AbstractAlgorithm::CHAR, QString("s"));
    paramh.append(paramh1);
    paramh.append(paramh2);
    AbstractAlgorithm* algh=Hierarchical::getInstance(paramh, QString("Hierarchical"), QString("Agglomerative (bottom-up) hierarchical clustering"));
    AlgorithmsList::getInstance()->addAlgorithm(algh);


    QList<AbstractAlgorithm::AlgorithmParameter> paramf;
    AbstractAlgorithm::AlgorithmParameter paramf1 (QString("epsilon"), AbstractAlgorithm::DOUBLE, QString("0.0001"));
    AbstractAlgorithm::AlgorithmParameter paramf2 (QString("Fuzzyness"), AbstractAlgorithm::INT, QString("2"));
    paramf.append(paramf1);
    paramf.append(paramf2);
    AbstractAlgorithm* algf=FuzzyCMeans::getInstance(paramf, QString("Fuzzy C-Means"), QString("Partitioning clustering method, overlapping (soft) assignment"));
    AlgorithmsList::getInstance()->addAlgorithm(algf);


    loader->loadFeatures(dataHome.absolutePath().append("/features.xml"), getFeaturesList());
    loader->loadAlgorithms(dataHome.absolutePath().append("/algorithms.xml"), getAlgorithmsList());
    loader->loadProtocols(dataHome.absolutePath().append("/protocols.xml"), getProtocolsList());
    loader->loadDatasetsNames(dataHome.absolutePath().append("/datasets.xml"));

    DatasetsList* datasetsList=getDatasetsList();
    connect(getAlgorithmsList(), SIGNAL(algorithmsListModified()), writer, SLOT(saveAlgorithmsList()));
    connect(getFeaturesList(), SIGNAL(featuresListModified()), writer, SLOT(saveFeaturesList()));
    connect(getProtocolsList(), SIGNAL(protocolsListModified()), writer, SLOT(saveProtocolsList()));
    connect(datasetsList, SIGNAL(datasetsListModified()), writer, SLOT(saveDatasetsList()));
    connect(datasetsList, SIGNAL(datasetDeleted(QString)), this, SLOT(deleteDataset(QString)));
    connect(datasetsList, SIGNAL(datasetModified(QString)), writer, SLOT(saveDataset(QString)));
}




void ModelCore::createLists()
{
    DatasetsList::getInstance(this);
    ProtocolsList::getInstance(this);
    algorithms::AlgorithmsList::getInstance(this);
    features::FeaturesList::getInstance(this);
}

void ModelCore::deleteDataset(QString datasetName)
{
    QFile file;
    file.setFileName(dataHome.absolutePath()+ "/" + datasetName +".xml");
    if (file.exists()){
        file.remove();
    }
}
QDir ModelCore::getDataHome()
{
    return dataHome;
}



ModelCore* ModelCore::getInstance(QObject *parent){
    if(instance == 0){
        instance = new ModelCore(parent);
    }
    return instance;
}

DatasetsList* ModelCore::getDatasetsList()
{
    return DatasetsList::getInstance(this);
}


features::FeaturesList* ModelCore::getFeaturesList()
{
    return FeaturesList::getInstance(this);
}

algorithms::AlgorithmsList* ModelCore::getAlgorithmsList()
{
    return AlgorithmsList::getInstance(this);
}


ProtocolsList* ModelCore::getProtocolsList()
{
    return ProtocolsList::getInstance(this);
}
