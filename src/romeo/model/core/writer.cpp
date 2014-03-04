#include "writer.h"
#include "modelcore.h"
#include <QtXml>
#include <QXmlStreamWriter>
#include <src/romeo/model/protocols/features/abstractfeature.h>
#include <src/romeo/model/protocols/algorithms/abstractalgorithm.h>
#include <src/romeo/model/protocols/algorithms/userdefinedalgorithm.h>
#include <src/romeo/model/datasets/abstractdataset.h>

using namespace romeo::model::datasets;
using namespace romeo::model::core;
using namespace romeo::model::protocols;
using namespace romeo::model::protocols::features;
using namespace romeo::model::protocols::algorithms;

Writer* Writer::instance=0;

Writer *Writer::getInstance(QObject *parent)
{
    if(instance == 0)
    {
        instance=new Writer(parent);
    }
    return instance;
}

Writer::Writer(QObject* parent): QObject(parent)
{
}

bool Writer::saveDatasetsList()
{
    QFile file(ModelCore::getDataHome().absolutePath().append("/datasets.xml"));
    if(!file.open(QFile::WriteOnly))
    {
        return false;
    }
    QXmlStreamWriter writer;
    writer.setDevice(&file);
    writer.setAutoFormatting(true);
    writer.writeStartDocument();
    writer.writeStartElement("datasets");
    QList<QString> datasetList=datasets::DatasetsList::getInstance()->getDatasetsFiles();
    for(int i=0; i< datasetList.length(); ++i)
    {
        AbstractDataset* dataset=DatasetsList::getInstance()->getDataset(datasetList.at(i));
        writer.writeStartElement("dataset");
        writer.writeAttribute("name", datasetList.at(i));
        writer.writeAttribute("type", dataset->getTypeString());
        writer.writeEndElement();
    }
    writer.writeEndElement();
    writer.writeEndDocument();
}

bool Writer::saveProtocolsList()
{
    QString dataHome=ModelCore::getInstance()->getDataHome().absolutePath();
    QFile file(dataHome.append("/protocols.xml"));
    if(!file.open(QFile::WriteOnly))
    {
        return false;
    }
    QXmlStreamWriter writer;
    writer.setDevice(&file);
    writer.setAutoFormatting(true);
    QList<AbstractProtocol*> protocolsList=ModelCore::getInstance()->getProtocolsList()->getProtocolsList();
    writer.writeStartDocument();
    writer.writeStartElement("protocols");
    for(int i=0; i < protocolsList.length() ; ++i)
    {
        writer.writeStartElement("protocol");
        writer.writeTextElement("name", protocolsList[i]->getName());
        writer.writeTextElement("description", protocolsList[i]->getDescription());
        ProtocolType ptype= protocolsList[i]->getType();
        bool staticProtocol=false;
        if( ptype == protocols::STATIC )
        {
            staticProtocol=true;
            writer.writeTextElement("type", "STATIC" );
        }
        else{
            writer.writeTextElement("type", "DYNAMIC" );
        }
        if (protocolsList[i]->getTest()){
            writer.writeTextElement("test", "true" );
        }
        else{
            writer.writeTextElement("test", "false" );
        }
        writer.writeTextElement("algorithm", protocolsList[i]->getAlgorithmName());
        writer.writeTextElement("nCluster", QString::number(protocolsList[i]->getNClusters()));
        QList<QString> algParameters =protocolsList[i]->getAlgorithmParameters();
        for(int i=0; i<algParameters.length(); ++i)
        {
            writer.writeTextElement("parameter", algParameters.at(i));
        }
        Writer::writeProtocolFeatures(protocolsList[i]->getFeaturesName(), writer);
        writer.writeTextElement("window", QString::number(protocolsList[i]->getWindowSize()));
        writer.writeTextElement("glcm", QString::number(protocolsList[i]->getDistanceToGlcm()));
        writer.writeEndElement(); //end protocol
    }
    writer.writeEndElement(); //end protocols
    writer.writeEndDocument();
    file.close();
}

bool Writer::saveAlgorithmsList()
{
    QString dataHome=ModelCore::getInstance()->getDataHome().path();
    QFile file(dataHome.append("/algorithms.xml"));
    if(!file.open(QFile::WriteOnly))
    {
        return false;
    }
    QXmlStreamWriter writer;
    writer.setDevice(&file);
    writer.setAutoFormatting(true);
    QList<AbstractAlgorithm*> algorithmsList=ModelCore::getInstance()->getAlgorithmsList()->getAlgorithmsList();
    //creo la lista con solo gli algoritmi definiti dall'utente
    QList<UserDefinedAlgorithm*> userAlgorithms;
    for(int i=0; i<algorithmsList.length(); ++i)
    {
        UserDefinedAlgorithm* uAlg=dynamic_cast<UserDefinedAlgorithm*> (algorithmsList[i]);
        if(uAlg){
            userAlgorithms.append(uAlg);
        }
    }

    writer.writeStartDocument();
    writer.writeStartElement("algorithms");
    for(int i=0; i < userAlgorithms.length(); ++i)
    {
        writer.writeStartElement("algorithm");
        writer.writeTextElement("name", userAlgorithms[i]->getName());
        writer.writeTextElement("description", userAlgorithms[i]->getDescription());
        writer.writeStartElement("parameterList");
        QList<AbstractAlgorithm::AlgorithmParameter> paramList=userAlgorithms[i]->getParameters();
        for( int j=0; j<paramList.length(); ++j)
        {
            writer.writeStartElement("parameter");
            writer.writeTextElement("pname", paramList.at(j).getName());
            writer.writeTextElement("type", paramList.at(j).getTypeString());
            writer.writeTextElement("default", paramList.at(j).getDefaultParameter());
            writer.writeEndElement();
        }
        writer.writeEndElement();
        writer.writeTextElement("file", userAlgorithms[i]->getDynamicLibraryPath());
        writer.writeTextElement("functionName", userAlgorithms[i]->getDynamicFunctionName());
        writer.writeEndElement(); //end algorithm
    }
    writer.writeEndElement();  //end algorithms
    writer.writeEndDocument();
    file.close();
}

bool Writer::saveFeaturesList()
{
    QString dataHome=ModelCore::getInstance()->getDataHome().path();

     QFile file(dataHome.append("/features.xml"));
    if(!file.open(QFile::WriteOnly))
    {
        return false;
    }
    QXmlStreamWriter writer;
    writer.setDevice(&file);
    writer.setAutoFormatting(true);
    QList<AbstractFeature*> featureList=ModelCore::getInstance()->getFeaturesList()->getFeaturesList();
    writer.writeStartDocument();
    writer.writeStartElement("features");
    for(int i=0; i < featureList.length(); ++i)
    {
        writer.writeStartElement("feature");
        writer.writeTextElement("name", featureList[i]->getName());
        writer.writeTextElement("description", featureList[i]->getDescription());

        FeatureType featType=featureList[i]->getType();
        if(featType == FIRSTORDER)
            writer.writeTextElement("type", "FIRSTORDER" );
        else if( featType == SECONDORDER)
            writer.writeTextElement("type", "SECONDORDER" );
        else writer.writeTextElement("type", "DYNAMIC" );

        writer.writeTextElement("file", featureList[i]->getDynamicLibraryPath());
        writer.writeTextElement("functionName", featureList[i]->getDynamicFunctionName());
        writer.writeEndElement();
    }
    writer.writeEndElement();
    writer.writeEndDocument();

    file.close();

}

bool Writer::saveDataset(const QString &datasetName)
{
    QString dataHome=ModelCore::getInstance()->getDataHome().path();
    QString datasetFile=dataHome.append("/");
    QFile file(datasetFile.append(QString(datasetName).append(".xml")));
    if(!file.open(QFile::WriteOnly))
    {
        return false;
    }
    AbstractDataset* dataset=DatasetsList::getInstance()->getDataset(datasetName);

    QXmlStreamWriter writer;
    writer.setDevice(&file);
    writer.setAutoFormatting(true);
    writer.writeStartDocument();
    writer.writeStartElement("dataset");
    writer.writeTextElement("name", dataset->getName());
    switch (dataset->getType()) {
    case TYPE2D:
        writer.writeTextElement("type", "TYPE2D");
        break;
    case TYPE3D:
        writer.writeTextElement("type", "TYPE3D");
        break;
    case TYPE2DT:
        writer.writeTextElement("type", "TYPE2DT");
        break;
    case TYPE3DT:
        writer.writeTextElement("type", "TYPE3DT");
        break;
    }
    Writer::writeDatasetSubjects(dataset, writer);
    Writer::writeDatasetProtocols(dataset, writer);
    writer.writeEndElement(); //end dataset
    writer.writeEndDocument();
}

void Writer::writeDatasetSubjects(const AbstractDataset *dataset, QXmlStreamWriter &writer)
{
    QList<AbstractSubject*> subjectList= dataset->getSubjectList();
    writer.writeStartElement("subjects");
    for(int i=0; i< subjectList.length(); ++i)
    {
        writer.writeEmptyElement("subject");
        writer.writeAttribute("name", subjectList[i]->getName());
        writer.writeAttribute("img", subjectList[i]->getSubject());
        writer.writeAttribute("mask", subjectList[i]->getMask());
    }
    writer.writeEndElement(); //end subjects
}

void Writer::writeDatasetProtocols(const AbstractDataset *dataset, QXmlStreamWriter &writer)
{
    QList<AbstractProtocol*> protocolList=dataset->getProtocolList();
    writer.writeStartElement("protocols");
    for (int i=0; i< protocolList.length(); ++i)
    {
        writer.writeStartElement("protocol");
        writer.writeAttribute("name", protocolList[i]->getName());
        QList<Result*> protocolResults= dataset->getResultsList(protocolList[i]->getName());
        writer.writeStartElement("results");
        for( int i=0; i< protocolResults.length(); ++i)
        {
            writer.writeEmptyElement("result");
            writer.writeAttribute("path", protocolResults.at(i)->getResultPath());
            QString date=protocolResults.at(i)->getExecutionDate().toString();
            writer.writeAttribute("date", date);
        }
        writer.writeEndElement(); //end results
        writer.writeEndElement();//end protocol
    }
    writer.writeEndElement(); //end protocols
}

void Writer::writeProtocolFeatures(QStringList featureNames, QXmlStreamWriter &writer)
{
    writer.writeStartElement("features");
    for(int i=0; i<featureNames.length(); ++i)
    {
        writer.writeTextElement("feature", featureNames.at(i));
    }
    writer.writeEndElement(); // end features
}


