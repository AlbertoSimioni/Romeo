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
