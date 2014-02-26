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

AbstractFeature::AbstractFeature(QString n, QString dylp, QString dyfn, QString desc):
    name(n), dynamicLibraryPath(dylp), dynamicFunctionName(dyfn), description(desc)
{
}
