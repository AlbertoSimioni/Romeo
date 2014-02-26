#include "writer.h"
#include "modelcore.h"
#include <QtXml>
#include <QXmlStreamWriter>
#include <QMessageBox>

#include <src/romeo/model/protocols/features/abstractfeature.h>
using namespace romeo::model::core;
using namespace romeo::model::protocols::features;

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
    return true;
}

bool Writer::saveProtocolsList()
{
    //writer->writeProtocols(QDir());
}

bool Writer::saveAlgorithmsList()
{
    //writer->writeAlgorithms(QDir());
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
    QFile::copy(dataHome.append("/features.xml"), dataHome.append("/features.backup"));
}

bool Writer::saveDataset(QString &datasetName)
{
    return true;
}
