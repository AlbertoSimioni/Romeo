#include "dataset2dt.h"
#include "subject2dt.h"

using namespace romeo::model::datasets;
Dataset2DT::Dataset2DT(QString &name): AbstractDataset(name)
{
}

AbstractSubject *Dataset2DT::makeSubject(QString &name, QString &fileSubject, QString &mask)
{
    return new Subject2DT(name, fileSubject, mask);
}
