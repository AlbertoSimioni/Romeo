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


AbstractFeature::AbstractFeature()
{
}
