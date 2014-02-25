#include "datasetslist.h"
#include "dataset2d.h"
#include "dataset2dt.h"
#include "dataset3d.h"
#include "dataset3dt.h"

using namespace romeo::model::datasets;

DatasetsList* DatasetsList::instance=0;
DatasetsList *DatasetsList::getInstance(QObject* parent)
{
    if(instance ==0 )
    {
        instance=new DatasetsList(parent);
    }
    return instance;
}

AbstractDataset *DatasetsList::getDataset(QString name) const
{
    for(int ind=0; ind<datasets.length(); ++ind)
    {
        if(datasets[ind]->getName() == name)
        {
            return datasets[ind];
        }
    }
    return 0;
}

void DatasetsList::addDataset(QString name, romeo::model::InputFormat datasetType)
{
    switch (datasetType) {
    case TYPE2D:
        datasets.append(new Dataset2D(name));
        break;
    case TYPE2DT:
        datasets.append(new Dataset2DT(name));
        break;
    case TYPE3D:
        datasets.append(new Dataset3D(name));
        break;
    case TYPE3DT:
        datasets.append(new Dataset3DT(name));
        break;
    default:
        break;
    }
    emit datasetsListModified();

}

QList<AbstractDataset*> DatasetsList::getDatasetsList() const {
    return datasets;
}

DatasetsList::~DatasetsList()
{
    for(int i=0; i<datasets.length(); ++i)
    {
        if(datasets.at(i))
            delete datasets.at(i);
    }
}

DatasetsList::DatasetsList(QObject *parent): QObject(parent)
{
}
