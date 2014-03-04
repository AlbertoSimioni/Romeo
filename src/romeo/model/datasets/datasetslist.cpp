#include "datasetslist.h"
#include "dataset2d.h"
#include "dataset2dt.h"
#include "dataset3d.h"
#include "dataset3dt.h"
#include<QDebug>
#include <src/romeo/model/core/writer.h>

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
    for(int i=0; i<datasets.length(); ++i){
        if( name == datasets.at(i)->getName())
            return;
    }
    AbstractDataset* newDataset=0;
    switch (datasetType) {
    case TYPE2D:
        newDataset=new Dataset2D(name);
        break;
    case TYPE2DT:
        newDataset=new Dataset2DT(name);
        break;
    case TYPE3D:
        newDataset=new Dataset3D(name);
        break;
    case TYPE3DT:
        newDataset=new Dataset3DT(name);
        break;
    default:
        break;
    }
    if(newDataset){
        datasets.append(newDataset);
        connect(newDataset, SIGNAL(modified(QString)), this, SIGNAL(datasetModified(QString)));
        emit datasetsListModified();
        emit datasetModified(name);
    }
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
    datasets.clear();
}

DatasetsList::DatasetsList(QObject *parent): QObject(parent)
{
}
QList<QString> DatasetsList::getDatasetsFiles() const
{
    QList<QString> datasetList;
    for(int i=0; i< datasets.length(); ++i)
    {
        datasetList.append(datasets.at(i)->getName());
    }
    return datasetList;
}

void DatasetsList::addDatasetFile(const QString &name)
{
    if(!datasetsFiles.contains(name))
    {
        datasetsFiles.append(name);
        emit datasetsListModified();
    }
}


AbstractDataset* DatasetsList::getNextDataset(AbstractDataset* dataset){
    AbstractDataset* nextDataset = 0;
    bool stop = false;
    for(int i = 0; i < datasets.size() && !stop; i++){
        if(datasets[i] != dataset){
            nextDataset = datasets[i];
            stop = true;
        }
    }
    return nextDataset;
}


void DatasetsList::deleteDataset(AbstractDataset *dataset){
    bool findedDataset = false;
    QString name=dataset->getName();
    for(int i = 0; i < datasets.size() && !findedDataset; i++ ){
        if(datasets[i] == dataset){
           delete datasets.takeAt(i);
            findedDataset = true;
        }

    }
    if(findedDataset)
    {
        emit datasetDeleted(name);
        emit datasetsListModified();
    }

}


void DatasetsList::deleteProtocolAssociations(QString protocolName){
    for(int i = 0; i < datasets.size(); i++){
        datasets[i]->removeProtocolAssociation(protocolName);
    }
}

