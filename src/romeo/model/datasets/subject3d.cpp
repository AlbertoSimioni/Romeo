#include "subject3d.h"
using namespace romeo::model::datasets;
Subject3D::Subject3D(QString &name, QString &imagePath, QString &maskPath): AbstractSubject(name, imagePath, maskPath)
{
}

QString Subject3D::getType()
{
    return QString("3D");
}
