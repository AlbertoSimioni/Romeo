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

DatasetsList::DatasetsList(QObject *parent): QObject()
{
}
