/**
* \file abstractstaticfeature.cpp
* \author Alberto Cavallarin
* \date 17-02-2014
**
* \brief  Header della classe AbstractStaticFeature del package romeo::model::protocols::features
*/

#include "abstractstaticfeature.h"
using namespace romeo::model::protocols::features;
AbstractStaticFeature::AbstractStaticFeature(QString n,QString dylp,QString dyfn,QString desc ):
    AbstractFeature(n,dylp,dyfn,desc)
{
}
