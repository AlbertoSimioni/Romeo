#include "dynamicfeature.h"
using namespace romeo::model::protocols::features;

DynamicFeature::DynamicFeature(QString n, QString dylp, QString dyfn, QString desc):
    AbstractFeature(n,dylp,dyfn,desc)
{
}


FeatureType DynamicFeature::getType(){
    return DYNAMIC;
}
