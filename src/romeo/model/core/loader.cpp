#include <QString>
#include <QFile>
#include <QIODevice>
#include <QDomDocument>
#include "loader.h"
#include "modelcore.h"
#include <src/romeo/model/protocols/algorithms/algorithmslist.h>
#include <src/romeo/model/protocols/features/featureslist.h>

using namespace romeo::model::core;
using namespace romeo::model::protocols::algorithms;
using namespace romeo::model::protocols::features;

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

    if( type.compare("FIRSTORDER", Qt::CaseInsensitive))
    {
        featureList->addFeature(name, FIRSTORDER, description, dyln, dyfn);
    }
    else if( type.compare("SECONDORDER", Qt::CaseInsensitive))
    {
        featureList->addFeature(name, SECONDORDER, description, dyln, dyfn);
    }
    else
    {
        if( type.compare("DYNAMIC", Qt::CaseInsensitive))
            featureList->addFeature(name, DYNAMIC, description, dyln, dyfn);
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
    if (typeString.compare("STATIC", Qt::CaseInsensitive))
    {
        type=protocols::STATIC;
    }
    else{
        type=protocols::DYNAMIC;
    }

    nextElement=nextElement.nextSiblingElement("test");
    testString=nextElement.text();

    bool test=testString.compare("true", Qt::CaseInsensitive);
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
        if(type.compare("INT"), Qt::CaseInsensitive)
            ptype=AbstractAlgorithm::INT;
        else if(type.compare("DOUBLE"), Qt::CaseInsensitive)
            ptype=AbstractAlgorithm::DOUBLE;
        else if(type.compare("BOOL"), Qt::CaseInsensitive)
            ptype=AbstractAlgorithm::BOOL;
        else
        {
            if(type.compare("CHAR"), Qt::CaseInsensitive)
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

