#include "modelcore.h"
using namespace romeo::model::core;
using namespace romeo::model::imageIO;
using namespace romeo::model::datasets;
using namespace romeo::model::protocols;



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


ModelCore* ModelCore::instance=0;
QDir ModelCore::dataHome=QDir::current();
ModelCore::ModelCore(QObject *parent): QObject(parent)
{
    writer=Writer::getInstance(this);
    loader=Loader::getInstance(this);
    dataHome=QDir::current();
    if(!dataHome.cd("data"))
    {
        qDebug("non ho trovato la cartella data nel path dell'applicazione. i file saranno salvati nella cartella d'esecuzione");
    }
    createLists();




    ////////////PROVA TEST
        /* QList<AbstractAlgorithm::AlgorithmParameter> param;
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

    */
        ///////////////PROVA TEST



    loader->loadFeatures(dataHome.absolutePath().append("/features.xml"), featuresList);
    loader->loadAlgorithms(dataHome.absolutePath().append("/algorithms.xml"), algorithmsList);
    loader->loadProtocols(dataHome.absolutePath().append("/protocols.xml"), protocolsList);
    loader->loadDatasetsNames(dataHome.absolutePath().append("/datasets.xml"));

    ///////////prova test
    /*!
    datasetsList->addDataset("PROVO",TYPE2D);

    AbstractDataset* dataset = datasetsList->getDataset("PROVO");
    AbstractProtocol * protocol = protocolsList->getProtocol("PROVA");
    if(dataset){
        dataset->associateProtocol(protocol);;

    dataset->addResult(protocol,new Result(QDate(1982,10,5),"/home/alberto/Scrivania/Dati/"));
    }*/
    ////////// provatest

    connect(algorithmsList, SIGNAL(algorithmsListModified()), writer, SLOT(saveAlgorithmsList()));
    connect(featuresList, SIGNAL(featuresListModified()), writer, SLOT(saveFeaturesList()));
    connect(protocolsList, SIGNAL(protocolsListModified()), writer, SLOT(saveProtocolsList()));
    connect(datasetsList, SIGNAL(datasetsListModified()), writer, SLOT(saveDatasetsList()));
}


//test
void ModelCore::save(){
    writer->saveAlgorithmsList();
    writer->saveFeaturesList();
    writer->saveProtocolsList();

}
//test

void ModelCore::createLists()
{
    datasetsList=DatasetsList::getInstance(this);
    protocolsList=ProtocolsList::getInstance(this);
    algorithmsList=algorithms::AlgorithmsList::getInstance(this);
    featuresList=features::FeaturesList::getInstance(this);
}
QDir ModelCore::getDataHome()
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
