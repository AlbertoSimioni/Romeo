#include "subject3d.h"
using namespace romeo::model::datasets;
using namespace romeo::model;
Subject3D::Subject3D(QString &name, QString &imagePath, QString &maskPath): AbstractSubject(name, imagePath, maskPath)
{
}

romeo::model::InputFormat Subject3D::getType()
{
    return TYPE3D;
}
