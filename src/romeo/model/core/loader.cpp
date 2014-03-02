#include <QString>
#include <QFile>
#include <QIODevice>
#include <QDomDocument>
#include "loader.h"
#include "modelcore.h"
#include <src/romeo/model/protocols/algorithms/algorithmslist.h>
#include <src/romeo/model/protocols/features/featureslist.h>
#include<QDebug>
#include <src/romeo/model/datasets/abstractdataset.h>
#include <src/romeo/model/protocols/protocolslist.h>

using namespace romeo::model::core;
using namespace romeo::model::protocols::algorithms;
using namespace romeo::model::protocols::features;
using namespace romeo::model::protocols;
using namespace romeo::model::datasets;

Loader* Loader::instance=0;
Loader *Loader::getInstance(QObject *parent)
{
    if(instance == 0){
        instance=new Loader(parent);
    }
    return instance;
}
Loader::Loader(QObject* parent): QObject(parent)
{
}

bool Loader::loadAlgorithms(const QString &algFile, AlgorithmsList* algorithmList)
{
    QFile file(algFile);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        return false;
    }
    QDomDocument doc;
    if(!doc.setContent(&file))
    {
        file.close();
        return false;
    }
    QDomElement docElem= doc.documentElement();
    QDomNodeList nodeList=docElem.elementsByTagName(QString("algorithm"));
    for(int i=0; i<nodeList.length(); ++i)
    {
        Loader::parseAlgorithm(algorithmList, nodeList.at(i));
    }
    file.close();
    return true;
}

bool Loader::loadFeatures(const QString& featFile, FeaturesList* featureList)
{
    QFile file(featFile);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        return false;
    }
    QDomDocument doc;
    if(!doc.setContent(&file))
    {
        file.close();
        return false;
    }
    QDomElement docElem= doc.documentElement();
    QDomNodeList nodeList=docElem.elementsByTagName(QString("feature"));
    for(int i=0; i<nodeList.length(); ++i)
    {
        parseFeature(featureList, nodeList.at(i));
    }
    file.close();
    return true;
}

bool Loader::loadProtocols(const QString &protocolFile, romeo::model::protocols::ProtocolsList *protocolList)
{
    QFile file(protocolFile);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        return false;
    }
    QDomDocument doc;
    if(!doc.setContent(&file))
    {
        file.close();
        return false;
    }
    QDomElement docElem= doc.documentElement();
    QDomNodeList nodeList=docElem.elementsByTagName(QString("protocol"));
    for(int i=0; i<nodeList.length(); ++i)
    {
        parseProtocol(protocolList, nodeList.at(i));
    }
    file.close();
    return true;
}

bool Loader::loadDatasetsNames(const QString &datasetsFile)
{
    QFile file(datasetsFile);
    if(!file.open(QIODevice::ReadOnly))
    {
        return false;
    }
    QDomDocument doc;
    if(!doc.setContent(&file))
    {
        file.close();
        return false;
    }
    QDomElement docElem= doc.documentElement();
    QDomNodeList nodeList=docElem.elementsByTagName(QString("dataset"));
    QString name;
    QString datasetFile;
    for(int i=0; i<nodeList.length(); ++i)
    {
        QDomElement elem=nodeList.at(i).toElement();
        name=elem.attribute("name");
        datasetFile=elem.attribute("file");
        datasets::DatasetsList::getInstance()->addDatasetFile(name, datasetFile);
    }
    file.close();
    return true;
}

bool Loader::LoadDataset(const QString &datasetFile)
{
    QFile file(datasetFile);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        return false;
    }
    QDomDocument doc;
    if(!doc.setContent(&file))
    {
        file.close();
        return false;
    }
    QDomElement docElem= doc.documentElement();
    QDomElement nameElem= docElem.firstChildElement("name");
    QDomElement typeElem= docElem.firstChildElement("type");
    AbstractDataset* dataset=DatasetsList::getInstance()->getDataset(nameElem.text());
    if(!dataset){
        return false;
    }
    QDomNodeList subjectList=docElem.elementsByTagName(QString("subject"));
    for(int i=0; i<subjectList.length(); ++i)
    {
        QString sName=subjectList.at(i).toElement().attribute("name");
        QString sImg=subjectList.at(i).toElement().attribute("img");
        QString sMask=subjectList.at(i).toElement().attribute("mask");
        dataset->makeSubject(sName, sImg, sMask);
    }

    QDomNodeList protocolList=docElem.elementsByTagName(QString("protocol"));
    for( int i=0; i< protocolList.length(); ++i)
    {
        QDomElement protocolElem=protocolList.at(i).toElement();
        QString protocolName=protocolElem.attribute("name");
        dataset->associateProtocol(ProtocolsList::getInstance()->getProtocol(protocolName));
        QDomNodeList results=protocolElem.elementsByTagName("result");
        for (int i=0; i< results.length(); ++i)
        {
            dataset->addResult(protocolName, results.at(i).toElement().text());
        }
    }
    file.close();
    return true;
}

bool Loader::parseFeature(FeaturesList* featureList,const QDomNode& node)
{
    QString name;
    QString description;
    QString dyln;
    QString dyfn;
    QString type;
    QDomElement nextElement=node.firstChildElement();

    if( nextElement.tagName() == "name"){
        name=nextElement.text();
    }
    nextElement=nextElement.nextSiblingElement("description");
    if(!nextElement.isNull()){
        description=nextElement.text();
    }
    nextElement=nextElement.nextSiblingElement("type");
    if(!nextElement.isNull()){
        type=nextElement.text();
    }
    nextElement=nextElement.nextSiblingElement("file");
    dyln=nextElement.text();
    nextElement=nextElement.nextSiblingElement("functionName");
    dyfn=nextElement.text();

    if( type == "FIRSTORDER")
    {
        featureList->addFeature(name, FIRSTORDER, description, dyln, dyfn);
    }
    else if( type =="SECONDORDER")
    {
        featureList->addFeature(name, SECONDORDER, description, dyln, dyfn);
    }
    else
    {
        if( type =="DYNAMIC")
            featureList->addFeature(name, features::DYNAMIC, description, dyln, dyfn);
    }
    return true;
}

bool Loader::parseAlgorithm(AlgorithmsList *algorithmsList, const QDomNode &node)
{
    QString name;
    QString description;
    QString dyln;
    QString dyfn;
    QList<AbstractAlgorithm::AlgorithmParameter> parameters;

    QDomElement nextElement=node.firstChildElement();
    if( nextElement.tagName() == "name"){
        name=nextElement.text();
    }
    nextElement=nextElement.nextSiblingElement("description");
    if(!nextElement.isNull()){
        description=nextElement.text();
    }
    nextElement=nextElement.nextSiblingElement("parameterList");
    if(!nextElement.isNull()){
        QDomNodeList paramList=nextElement.elementsByTagName("parameter");
        for(int i=0; i<paramList.length(); ++i)
        {
            parseParameter( parameters, paramList.at(i));
        }
    }
    nextElement=nextElement.nextSiblingElement("file");
    dyln=nextElement.text();
    nextElement=nextElement.nextSiblingElement("functionName");
    dyfn=nextElement.text();

    algorithmsList->addAlgorithm(name, description, parameters, dyln, dyfn);
    return true;
}

bool Loader::parseProtocol(romeo::model::protocols::ProtocolsList *protocolsList, const QDomNode &node)
{
    QString name, description, typeString, testString;
    QString algorithm;
    QList<AbstractFeature*> featureList;
    AbstractAlgorithm* alg=0;
    protocols::ProtocolType type;
    int window=0;
    int glcm=0;

    QDomElement nextElement=node.firstChildElement("name");
    name=nextElement.text();
    nextElement=nextElement.nextSiblingElement("description");
    description=nextElement.text();
    nextElement=nextElement.nextSiblingElement("type");
    typeString=nextElement.text();
    if (typeString == "STATIC")
    {
        type=protocols::STATIC;
    }
    else{
        type=protocols::DYNAMIC;
    }

    nextElement=nextElement.nextSiblingElement("test");
    testString=nextElement.text();
    bool test=testString == "true";
    nextElement=nextElement.nextSiblingElement("algorithm");
    algorithm=nextElement.text();
    alg=AlgorithmsList::getInstance()->getAlgorithm(algorithm);

    nextElement=nextElement.nextSiblingElement("features");
    QDomNodeList featureNames=nextElement.elementsByTagName("feature");
    for(int i=0; i<featureNames.length(); ++i)
    {
        QString fName=featureNames.at(i).toElement().text();
        AbstractFeature* parsedFeature=FeaturesList::getInstance()->getFeature(fName);
        if(parsedFeature)
            featureList.append(parsedFeature);
    }

    nextElement=nextElement.nextSiblingElement("window");
    window = nextElement.text().toInt();
    if ( window<0 )
        window=3;

    nextElement=nextElement.nextSiblingElement("glcm");
    glcm=nextElement.text().toInt();
    if ( glcm<0 )
        glcm=1;
    protocolsList->addProtocol(name, description, alg, featureList, test, type, window, glcm );
    return true;
}

bool Loader::parseParameter(QList<AbstractAlgorithm::AlgorithmParameter>& list, const QDomNode& node)
{
    QString name, type, defaultValue;
    AbstractAlgorithm::ParameterType ptype;
    QDomElement nextElement=node.firstChildElement();
    if( nextElement.tagName() == "pname"){
        name=nextElement.text();
    }
    nextElement=nextElement.nextSiblingElement("type");
    if(!nextElement.isNull()){
        type=nextElement.text();
        if(type == "INT")
            ptype=AbstractAlgorithm::INT;
        else if(type == "DOUBLE")
            ptype=AbstractAlgorithm::DOUBLE;
        else if(type == "BOOL")
            ptype=AbstractAlgorithm::BOOL;
        else
        {
            if(type == "CHAR")
                ptype=AbstractAlgorithm::CHAR;
        }
    }
    nextElement=nextElement.nextSiblingElement("default");
    if(!nextElement.isNull()){
        defaultValue=nextElement.text();
    }
    AbstractAlgorithm::AlgorithmParameter algParam(name, ptype, defaultValue);
    list.append(algParam);
}

