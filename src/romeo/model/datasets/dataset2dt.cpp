#include "dataset2dt.h"
#include "subject2dt.h"

using namespace romeo::model::datasets;
using namespace romeo::model;
Dataset2DT::Dataset2DT(QString &name): AbstractDataset(name)
{
}

AbstractSubject *Dataset2DT::makeSubject(QString &name, QString &fileSubject, QString &mask)
{
    return new Subject2DT(name, fileSubject, mask);
}

InputFormat Dataset2DT::getType(){
    return TYPE2DT;
}
