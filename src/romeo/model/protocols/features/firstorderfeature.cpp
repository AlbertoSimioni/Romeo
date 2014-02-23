#include "firstorderfeature.h"
using namespace romeo::model::protocols::features;
FirstOrderFeature::FirstOrderFeature(QString n, QString dylp, QString dyfn, QString desc):
    AbstractStaticFeature(n,dylp,dyfn,desc)
{
}


FeatureType FirstOrderFeature::getType(){
    return FIRSTORDER;
}
