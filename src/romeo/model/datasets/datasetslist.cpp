#include "datasetslist.h"
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
