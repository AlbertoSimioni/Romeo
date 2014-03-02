#include "abstractfeature.h"
using namespace romeo::model::protocols::features;

QString AbstractFeature::getDynamicLibraryPath() const
{
    return dynamicLibraryPath;
}



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
