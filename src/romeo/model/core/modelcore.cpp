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
        dataHome.mkdir("data");
        dataHome.cd("data");
    }
    createLists();




    ////////////PROVA TEST
    //
        /*QList<AbstractAlgorithm::AlgorithmParameter> param;
        AbstractAlgorithm::AlgorithmParameter param1 (QString("param1"), AbstractAlgorithm::BOOL, QString("default"));
        AbstractAlgorithm::AlgorithmParameter param2 (QString("param2"), AbstractAlgorithm::CHAR, QString("default"));
        param.append(param1);
        param.append(param2);
        AbstractAlgorithm* alg=new UserDefinedAlgorithm(param, QString("Algoritmo1"), QString("desc"), QString("libreria"), QString("nomefunz"));
        AlgorithmsList::getInstance()->addAlgorithm(alg);

        QList<AbstractAlgorithm::AlgorithmParameter> params;
        AbstractAlgorithm::AlgorithmParameter param11 (QString("Param1"), AbstractAlgorithm::INT, QString("25"));
        AbstractAlgorithm::AlgorithmParameter param22 (QString("Param2"), AbstractAlgorithm::CHAR, QString("default"));
        params.append(param11);
        params.append(param22);
        AbstractAlgorithm* alg2=new UserDefinedAlgorithm(params, QString("Algoritmo"), QString("desc2"), QString("libreria"), QString("nomefunz"));
        AlgorithmsList::getInstance()->addAlgorithm(alg2);


        AbstractFeature* feat1 = new FirstOrderFeature("FeatureFO1","PATH","PATH","DESC1");
        AbstractFeature* feat2 = new FirstOrderFeature("FeatureFO2","PATH","PATH","DESC2");
        AbstractFeature* feat3 = new DynamicFeature("FeatureD1","PATH","PATH","DESC3");
        AbstractFeature* feat4 = new SecondOrderFeature("FeatureSO1","PATH","PATH","DESC4");
        FeaturesList::getInstance()->addFeature(feat1);
        FeaturesList::getInstance()->addFeature(feat2);
        FeaturesList::getInstance()->addFeature(feat3);
        FeaturesList::getInstance()->addFeature(feat4);


        QList<AbstractFeature*> features;
        features.append(feat1);
        features.append(feat2);
        features.append(feat4);
        ProtocolsList::getInstance()->addProtocol("PROVA","descrizione",alg,5,QList<QString>(),features,false, STATIC);

    */
        ///////////////PROVA TEST

    /*
    AbstractFeature* feat1 = new FirstOrderFeature("Standard Deviation",QDir::toNativeSeparators("features/libfeatures"),"feat_p1_std","gran bella descrizione");
    AbstractFeature* feat2 = new FirstOrderFeature("Mean",QDir::toNativeSeparators("features/libfeatures"),"feat_p1_mean","gran bella descrizione");
    AbstractFeature* feat3 = new FirstOrderFeature("Skewness",QDir::toNativeSeparators("features/libfeatures"),"feat_p1_skew","gran bella descrizione");
    AbstractFeature* feat4 = new FirstOrderFeature("Kurtosis",QDir::toNativeSeparators("features/libfeatures"),"feat_p1_kurt","gran bella descrizione");
    AbstractFeature* feat5 = new SecondOrderFeature("Contrast",QDir::toNativeSeparators("features/libfeatures"),"feat_p2_contr","gran bella descrizione");
    AbstractFeature* feat6 = new SecondOrderFeature("Correlation",QDir::toNativeSeparators("features/libfeatures"),"feat_p2_corr","gran bella descrizione");
    AbstractFeature* feat7 = new SecondOrderFeature("Energy",QDir::toNativeSeparators("features/libfeatures"),"feat_p2_energy","gran bella descrizione");
    AbstractFeature* feat8 = new SecondOrderFeature("Entropy",QDir::toNativeSeparators("features/libfeatures"),"feat_p2_entropy","gran bella descrizione");
    AbstractFeature* feat9 = new SecondOrderFeature("Homogeneity",QDir::toNativeSeparators("features/libfeatures"),"feat_p2_homo","gran bella descrizione");

    FeaturesList::getInstance()->addFeature(feat1);
    FeaturesList::getInstance()->addFeature(feat2);
    FeaturesList::getInstance()->addFeature(feat3);
    FeaturesList::getInstance()->addFeature(feat4);
    FeaturesList::getInstance()->addFeature(feat5);
    FeaturesList::getInstance()->addFeature(feat6);
    FeaturesList::getInstance()->addFeature(feat7);
    FeaturesList::getInstance()->addFeature(feat8);
    FeaturesList::getInstance()->addFeature(feat9);

    */


    loader->loadFeatures(dataHome.absolutePath().append("/features.xml"), getFeaturesList());
    loader->loadAlgorithms(dataHome.absolutePath().append("/algorithms.xml"), getAlgorithmsList());
    loader->loadProtocols(dataHome.absolutePath().append("/protocols.xml"), getProtocolsList());
    loader->loadDatasetsNames(dataHome.absolutePath().append("/datasets.xml"));

    ///////////prova test
/*
    DatasetsList::getInstance()->addDataset("PROVO",TYPE2D);

    AbstractDataset* dataset = DatasetsList::getInstance()->getDataset("PROVO");
    AbstractProtocol * protocol = ProtocolsList::getInstance()->getProtocol("PROVA");
    if(dataset){
        dataset->associateProtocol(protocol);;

    dataset->addResult(protocol,new Result(QDateTime(QDate(1982,10,5),QTime(15,30,30)),"/home/alberto/"));
    }*/
    ////////// provatest
    DatasetsList* datasetsList=getDatasetsList();
    connect(getAlgorithmsList(), SIGNAL(algorithmsListModified()), writer, SLOT(saveAlgorithmsList()));
    connect(getFeaturesList(), SIGNAL(featuresListModified()), writer, SLOT(saveFeaturesList()));
    connect(getProtocolsList(), SIGNAL(protocolsListModified()), writer, SLOT(saveProtocolsList()));
    connect(datasetsList, SIGNAL(datasetsListModified()), writer, SLOT(saveDatasetsList()));
    connect(datasetsList, SIGNAL(datasetDeleted(QString)), this, SLOT(deleteDataset(QString)));
    connect(datasetsList, SIGNAL(datasetModified(QString)), writer, SLOT(saveDataset(QString)));
}


//test
void ModelCore::save(){
    writer->saveAlgorithmsList();
    writer->saveFeaturesList();
    writer->saveProtocolsList();
    writer->saveDatasetsList();
}
//test

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
