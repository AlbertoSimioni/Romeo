#include "modelcore.h"
using namespace romeo::model::core;
using namespace romeo::model::imageIO;
using namespace romeo::model::datasets;
using namespace romeo::model::protocols;

ModelCore* ModelCore::instance=0;

ModelCore::ModelCore(QObject *parent): QObject(parent)
{
}

bool ModelCore::saveDatasetsList()
{
    return true;
}

bool ModelCore::saveProtocolsList()
{
    return true;
}

bool ModelCore::saveAlgorithmsList()
{
    return true;
}

bool ModelCore::saveFeaturesList()
{
    return true;
}
ModelCore* ModelCore::getInstance(QObject *parent){
    if(instance == 0){
        instance = new ModelCore(parent);
    }
    return instance;
}

DatasetsList *ModelCore::getDatasetsList() const
{
    return datasetsList;
}


features::FeaturesList *ModelCore::getFeaturesList() const
{
    return featuresList;
}

algorithms::AlgorithmsList *ModelCore::getAlgorithmsList() const
{
    return algorithmsList;
}


ProtocolsList *ModelCore::getProtocolsList() const
{
    return protocolsList;
}
