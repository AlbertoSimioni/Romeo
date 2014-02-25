#include "abstractdataset.h"
using namespace romeo::model::datasets;
AbstractDataset::AbstractDataset()
{
}

AbstractDataset::AbstractDataset(QString &n): name(n)
{
}

void AbstractDataset::createNewSubject(QString &name, QString &fileSubject, QString &mask)
{
    subjects.insert(this->makeSubject(name, fileSubject, mask), QList<Result*>());
    return;
}
QString AbstractDataset::getName() const
{
    return name;
}

void AbstractDataset::setName(QString &value)
{
    name = value;
}

