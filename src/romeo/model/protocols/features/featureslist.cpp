#include "dynamicfeature.h"
#include "featureslist.h"
#include "firstorderfeature.h"
#include "secondorderfeature.h"

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

FeaturesList::~FeaturesList()
{
    int k=features.length();
    for(int i=0; i<k && !features.isEmpty(); ++i)
    {
        delete features.takeLast();
    }
}

void FeaturesList::addFeature(const QString &name, FeatureType type, const QString &description, const QString &dylp, const QString &dyfn)
{
    //controllo che non ci siano altre feature nella lista con lo stesso nome
    bool ok=false;
    for(int i=0; i<features.length() && !ok; ++i)
    {
        if( features[i]->getName() == name){
            ok=true;
            return;
        }
    }
    AbstractFeature* newFeature=0;
    switch (type) {
    case FIRSTORDER:
        newFeature=new FirstOrderFeature(name, dylp, dyfn, description);
        break;
    case SECONDORDER:
        newFeature=new SecondOrderFeature(name, dylp, dyfn, description);
        break;
    case DYNAMIC:
        newFeature=new DynamicFeature(name, dylp, dyfn, description);
        break;
    default:
        break;
    }
    if(newFeature)
    {
        features.append(newFeature);
        emit featuresListModified();
    }
}


void  FeaturesList::addFeature(AbstractFeature *aa){
    //controllo che non ci siano altre feature nella lista con lo stesso nome
    bool ok=false;
    for(int i=0; i<features.length() && !ok; ++i)
    {
        if( features[i]->getName() == aa->getName()){
            ok=true;
            return;
        }
    }
    features.append(aa);
    emit FeaturesList::featuresListModified();
}

QList<AbstractFeature*> FeaturesList::getFeaturesList(){
    return features;
}

AbstractFeature *FeaturesList::getFeature(QString feature) const
{
    for(int ind=0; ind<features.length(); ++ind)
    {
        if(features[ind]->getName() == feature)
        {
            return features[ind];
        }
    }
    return 0;
}
