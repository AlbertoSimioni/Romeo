/**
* \file firstorderfeature.cpp
* \author Alberto Cavallarin
* \date 17-02-2014
**
* \brief  Header della classe FirstOrderFeature del package romeo::model::protocols::features
*/

#include "firstorderfeature.h"
using namespace romeo::model::protocols::features;
FirstOrderFeature::FirstOrderFeature(QString n, QString dylp, QString dyfn, QString desc):
    AbstractStaticFeature(n,dylp,dyfn,desc)
{
}


FeatureType FirstOrderFeature::getType(){
    return FIRSTORDER;
}
