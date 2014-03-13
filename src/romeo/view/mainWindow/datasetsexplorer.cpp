/**
* \file datasetexplorer.cpp
* \author Alessandro Strenghetto
* \date 2014-02-17
**
* \brief Header della classe DatasetExplorer del package romeo::view::mainWindow
*/

#include "datasetsexplorer.h"
#include "ui_datasetsexplorer.h"

using namespace romeo::view::mainWindow;
using namespace romeo::model::datasets;
using namespace romeo::model;

DatasetsExplorer::DatasetsExplorer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DatasetsExplorer)
{

    ui->setupUi(this);
    connectUI();
}

DatasetsExplorer::~DatasetsExplorer()
{
    delete ui;
}

void DatasetsExplorer::connectUI(){
    connect(ui->datasetsTable,SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)),this,SLOT(onItemDoubleClicked(QTreeWidgetItem*)));

}

romeo::model::datasets::DatasetsList *DatasetsExplorer::getDatasetsList() const
{
    return datasetsList;
}

void DatasetsExplorer::setDatasetsList(romeo::model::datasets::DatasetsList *value)
{
    datasetsList = value;
    connect(datasetsList,SIGNAL(datasetsListModified()),this,SLOT(fillDatasetsExplorer()));
    fillDatasetsExplorer();
}

void DatasetsExplorer::fillDatasetsExplorer(){
    ui->datasetsTable->clear();
    if(datasetsList){
        QList<AbstractDataset*> datasets = datasetsList->getDatasetsList();
        for(int i = 0; i < datasets.size(); i++){
            QTreeWidgetItem *itm =new QTreeWidgetItem(ui->datasetsTable);
            itm->setText(0,datasets[i]->getName());
            InputFormat format = datasets[i]->getType();
            QString formatString;
            switch(format){
            case TYPE2D: formatString = "2D";
                break;
            case TYPE3D: formatString = "3D";
                break;
            case TYPE2DT: formatString = "2D-t";
                break;
            case TYPE3DT: formatString = "3D-t";
                break;
            }
            itm->setText(1,formatString);
        }

    }
}


void DatasetsExplorer::onItemDoubleClicked(QTreeWidgetItem *item){
    emit currentDatasetChanged(item->data(0,Qt::DisplayRole).toString());
}
