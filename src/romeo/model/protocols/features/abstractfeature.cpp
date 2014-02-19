#include "abstractfeature.h"
using namespace romeo::model::protocols::features;

QString AbstractFeature::getDynamicLibraryPath() const
{
    return dynamicLibraryPath;
}


AbstractFeature::AbstractFeature()
{
}
