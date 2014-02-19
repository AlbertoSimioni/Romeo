#include "abstractdataset.h"
using namespace romeo::model::datasets;
AbstractDataset::AbstractDataset()
{
}
QString AbstractDataset::getName() const
{
    return name;
}

void AbstractDataset::setName(QString &value)
{
    name = value;
}

