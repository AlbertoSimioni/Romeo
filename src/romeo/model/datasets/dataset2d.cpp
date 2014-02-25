#include "dataset2d.h"
#include "subject2d.h"
using namespace romeo::model::datasets;
using namespace romeo::model;
Dataset2D::Dataset2D(QString &name): AbstractDataset(name)
{
}

AbstractSubject *Dataset2D::makeSubject(QString &name, QString &fileSubject, QString &mask)
{
    return new Subject2D(name, fileSubject, mask);
}

InputFormat Dataset2D::getType(){
    return TYPE2D;
}
