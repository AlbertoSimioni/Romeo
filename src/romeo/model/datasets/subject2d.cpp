#include "subject2d.h"
using namespace romeo::model::datasets;
Subject2D::Subject2D(QString &name, QString &imagePath, QString &maskPath): AbstractSubject(name, imagePath, maskPath)
{
}

QString Subject2D::getType()
{
    return QString("2D");
}
