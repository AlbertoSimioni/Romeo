/**
* \file subject2d.cpp
* \author Matteo Pozza
* \date 2014-02-17
**
* \brief Header della classe Subject2D del package romeo::model::datasets
*/

#include "subject2d.h"
using namespace romeo::model::datasets;
using namespace romeo::model;
Subject2D::Subject2D(QString &name, QString &imagePath, QString &maskPath): AbstractSubject(name, imagePath, maskPath)
{
}

romeo::model::InputFormat Subject2D::getType()
{
    return TYPE2D;
}
