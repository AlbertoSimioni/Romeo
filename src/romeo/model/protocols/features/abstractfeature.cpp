/**
* \file abstractfeature.cpp
* \author Alberto Cavallarin
* \date 17-02-2014
**
* \brief  Header della classe AbstractFeature del package romeo::model::protocols::features
*/


#include "abstractfeature.h"
using namespace romeo::model::protocols::features;

QString AbstractFeature::getDynamicLibraryPath() const
{
    return dynamicLibraryPath;
}



AbstractFeature::~AbstractFeature(){}

QString AbstractFeature::getName() const
{
    return name;
}


QString AbstractFeature::getDescription() const
{
    return description;
}



QString AbstractFeature::getDynamicFunctionName() const
{
    return dynamicFunctionName;
}

AbstractFeature::AbstractFeature(QString featureName, QString dylp, QString dyfn, QString description):
    name(featureName), dynamicLibraryPath(dylp), dynamicFunctionName(dyfn), description(description)
{
}
