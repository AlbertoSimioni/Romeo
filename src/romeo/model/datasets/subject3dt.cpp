/**
* \file subject3dt.cpp
* \author Matteo Pozza
* \date 2014-02-17
**
* \brief Header della classe Subject3DT del package romeo::model::datasets
*/

#include "subject3dt.h"
using namespace romeo::model::datasets;
using namespace romeo::model;
Subject3DT::Subject3DT(QString &name, QString &imagePath, QString &maskPath): AbstractSubject(name, imagePath, maskPath)
{
}

romeo::model::InputFormat Subject3DT::getType()
{
    return TYPE3DT;
}
