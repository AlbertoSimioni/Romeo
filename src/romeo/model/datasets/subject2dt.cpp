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
