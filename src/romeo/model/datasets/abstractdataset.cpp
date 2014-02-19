#include "abstractdataset.h"
using namespace romeo::model::datasets;
AbstractDataset::AbstractDataset()
{
}
QString AbstractDataset::getName()
{
    return name;
}

void AbstractDataset::setName(QString &value)
{
    name = value;
}

