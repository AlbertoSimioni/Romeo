#include "writer.h"
using namespace romeo::model::core;

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
    return true;
}

bool Writer::saveDataset(QString &datasetName)
{
    return true;
}
