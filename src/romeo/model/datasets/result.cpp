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



