#include "secondorderfeature.h"
using namespace romeo::model::protocols::features;
SecondOrderFeature::SecondOrderFeature(QString n,QString dylp,QString dyfn,QString desc ):
    AbstractStaticFeature(n,dylp,dyfn,desc)
{
}


FeatureType SecondOrderFeature::getType(){
    return SECONDORDER;
}
