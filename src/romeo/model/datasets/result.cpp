#include "result.h"
using namespace romeo::model::datasets;

bool Result::getFeatureResult() const
{
    return featureResult;
}


QString Result::getFeatureName() const
{
    return featureName;
}


QString Result::getProtocolName() const
{
    return protocolName;
}


QDate Result::getExecutionDate() const
{
    return executionDate;
}

QString Result::getResultPath() const
{
    return resultPath;
}


/*Result::Result()
{
}*/
