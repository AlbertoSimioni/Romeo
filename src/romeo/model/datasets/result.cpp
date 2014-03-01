#include "result.h"
using namespace romeo::model::datasets;


Result::Result(QDate execDate, QString pathToResult):
    executionDate(execDate), resultPath(pathToResult)
{

}

QDate Result::getExecutionDate() const
{
    return executionDate;
}

QString Result::getResultPath() const
{
    return resultPath;
}



