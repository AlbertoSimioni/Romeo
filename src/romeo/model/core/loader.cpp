#include <QMessageBox>
#include <QString>
#include <QFile>
#include <QIODevice>
#include <QDomDocument>
#include "loader.h"
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

bool Loader::loadAlgorithms(QString algFile, AbstractAlgorithm *algorithmList)
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

    QDomNodeList nodeList=doc.elementsByTagName(QString("algorithm"));
    for(int i=0; i<nodeList.length(); ++i)
    {
        //parseAlgorithm(algorithmList, nodeList.at(i));
    }

    file.close();
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

    QDomNodeList nodeList=doc.elementsByTagName(QString("feature"));
    for(int i=0; i<nodeList.length(); ++i)
    {
        parseFeature(featureList, nodeList.at(i));
    }

    file.close();
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
    if(!nextElement.isNull()){
        dyln=nextElement.text();
    }
    nextElement=nextElement.nextSiblingElement("functionName");
    if(!nextElement.isNull()){
        dyfn=nextElement.text();
    }

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
        QList<AbstractAlgorithm::AlgorithmParameter> parameters;
        QDomNodeList paramList=nextElement.elementsByTagName("parameter");
        for(int i=0; i<paramList.length(); ++i)
        {
            //parseParameter(paramList.at(i), parameters);
        }
    }


    nextElement=nextElement.nextSiblingElement("file");
    if(!nextElement.isNull()){
        dyln=nextElement.text();
    }
    nextElement=nextElement.nextSiblingElement("functionName");
    if(!nextElement.isNull()){
        dyfn=nextElement.text();
    }
    return true;
}

/*bool Loader::parseParameter(const QDomNode& node, QList<AbstractAlgorithm::AlgorithmParameter>& list)
{

}*/
