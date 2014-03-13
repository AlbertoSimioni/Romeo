/**
* \file dynamicfeature.cpp
* \author Alberto Cavallarin
* \date 17-02-2014
**
* \brief  Header della classe DynamicFeature del package romeo::model::protocols::features
*/

#include "dynamicfeature.h"
using namespace romeo::model::protocols::features;

DynamicFeature::DynamicFeature(QString n, QString dylp, QString dyfn, QString desc):
    AbstractFeature(n,dylp,dyfn,desc)
{
}


FeatureType DynamicFeature::getType(){
    return DYNAMIC;
}
