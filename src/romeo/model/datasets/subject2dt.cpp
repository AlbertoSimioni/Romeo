#include "subject2dt.h"
using namespace romeo::model::datasets;
Subject2DT::Subject2DT(QString &name, QString &imagePath, QString &maskPath): AbstractSubject(name, imagePath, maskPath)
{
}

QString Subject2DT::getType()
{
    return QString("2DT");
}
