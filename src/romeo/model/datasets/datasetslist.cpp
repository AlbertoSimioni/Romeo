#include "datasetslist.h"
#include "dataset2d.h"
#include "dataset2dt.h"
#include "dataset3d.h"
#include "dataset3dt.h"
#include<QDebug>

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
QHash<QString, QString> DatasetsList::getDatasetsFiles() const
{
    return datasetsFiles;
}

void DatasetsList::addDatasetFile(const QString &name, const QString &file)
{
    if(!datasetsFiles.contains(name))
    {
        datasetsFiles.insert(name, file);
    }
}


AbstractDataset* DatasetsList::getFirstDataset(){
    AbstractDataset* firstDataset = 0;
    if(!datasets.isEmpty()){
        firstDataset = datasets.at(0);
    }
    return firstDataset;
}


void DatasetsList::deleteDataset(AbstractDataset *dataset){
    datasets.removeAll(dataset);
    emit datasetsListModified();
}


void DatasetsList::deleteProtocolAssociations(QString protocolName){
    for(int i = 0; i < datasets.size(); i++){
        datasets[i]->removeProtocolAssociation(protocolName);
    }
}
