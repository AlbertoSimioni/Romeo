#include "datasetslist.h"
using namespace romeo::model::datasets;

DatasetsList* DatasetsList::instance=0;
DatasetsList *DatasetsList::getInstance()
{
    if(instance ==0 )
    {
        instance=new DatasetsList();
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

DatasetsList::DatasetsList(QObject *parent): QObject()
{
}
