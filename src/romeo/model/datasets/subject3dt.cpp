#include "subject3dt.h"
using namespace romeo::model::datasets;
Subject3DT::Subject3DT(QString &name, QString &imagePath, QString &maskPath): AbstractSubject(name, imagePath, maskPath)
{
}

QString Subject3DT::getType()
{
    return QString("3DT");
}
