#include "featureslist.h"
using namespace romeo::model::protocols::features;

FeaturesList* FeaturesList::instance=0;
FeaturesList::FeaturesList(QObject *parent) :
    QObject(parent)
{
}

FeaturesList *FeaturesList::getInstance(QObject* parent)
{
    if(instance == 0)
    {
        instance= new FeaturesList(parent);
    }
    return instance;
}


void  FeaturesList::addFeature(AbstractFeature *aa){
    features.append(aa);
}

QList<AbstractFeature*> FeaturesList::getFeaturesList(){
    return features;
}
