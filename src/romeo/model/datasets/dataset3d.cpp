#include "dataset3d.h"
#include "subject3d.h"
using namespace romeo::model::datasets;
Dataset3D::Dataset3D(QString &name): AbstractDataset(name)
{
}

AbstractSubject *Dataset3D::makeSubject(QString &name, QString &fileSubject, QString &mask)
{
    return new Subject3D(name, fileSubject, mask);
}
