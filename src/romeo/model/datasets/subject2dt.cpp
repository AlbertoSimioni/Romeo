/**
* \file subject2dt.cpp
* \author Matteo Pozza
* \date 2014-02-17
**
* \brief Header della classe Subject2DT del package romeo::model::datasets
*/

#include "subject2dt.h"
using namespace romeo::model::datasets;
using namespace romeo::model;
Subject2DT::Subject2DT(QString &name, QString &imagePath, QString &maskPath): AbstractSubject(name, imagePath, maskPath)
{
}

romeo::model::InputFormat Subject2DT::getType()
{
    return TYPE2DT;
}
