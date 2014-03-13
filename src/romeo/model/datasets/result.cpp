/**
* \file result.cpp
* \author Matteo Pozza
* \date 2014-02-17
**
* \brief Header della classe Result del package romeo::model::datasets
*/

#include "result.h"
using namespace romeo::model::datasets;


Result::Result(QDateTime execDate, QString pathToResult):
    executionDate(execDate), resultPath(pathToResult)
{
}

Result::Result(QString pathToResult): resultPath(pathToResult)
{
}

QDateTime Result::getExecutionDate() const
{
    return executionDate;
}

QString Result::getResultPath() const
{
    return resultPath;
}



