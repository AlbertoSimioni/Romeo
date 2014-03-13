/**
* \file secondorderfeature.cpp
* \author Alberto Cavallarin
* \date 17-02-2014
**
* \brief  Header della classe SecondOrderFeature del package romeo::model::protocols::features
*/

#include "secondorderfeature.h"
using namespace romeo::model::protocols::features;
SecondOrderFeature::SecondOrderFeature(QString n,QString dylp,QString dyfn,QString desc ):
    AbstractStaticFeature(n,dylp,dyfn,desc)
{
}


FeatureType SecondOrderFeature::getType(){
    return SECONDORDER;
}
