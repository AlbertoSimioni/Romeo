#include "datasetpanel.h"
#include "ui_datasetpanel.h"
using namespace romeo::view::mainWindow;
using namespace romeo::model::datasets;
DatasetPanel::DatasetPanel(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DatasetPanel)
{
    ui->setupUi(this);
    emptyPanel = new QWidget(this);

}

DatasetPanel::~DatasetPanel()
{
    delete ui;
}
romeo::model::datasets::AbstractDataset *DatasetPanel::getCurrentDataset() const
{
    return currentDataset;
}

void DatasetPanel::setCurrentDataset(romeo::model::datasets::AbstractDataset *dataset)
{

   /* if((currentDataset != 0) && (dataset == 0)){
        ui->horizontalLayout->removeWidget(ui->subjectsPanel);
        ui->horizontalLayout->removeItem(ui->verticalLayout);
        ui->horizontalLayout->addWidget(emptyPanel);
    }
    if((currentDataset == 0) && (dataset != 0)){
        ui->horizontalLayout->removeWidget(emptyPanel);
        ui->horizontalLayout->addWidget(ui->subjectsPanel);
        ui->horizontalLayout->addItem(ui->verticalLayout);
    }

    currentDataset = dataset;
    if(currentDataset != 0){*/
        ui->protocolsPanel->setCurrentDataset(currentDataset);
        ui->subjectsPanel->setCurrentDataset(currentDataset);
    //}
}


ProtocolsPanel* DatasetPanel::getProtocolsPanel(){
    return ui->protocolsPanel;
}


SubjectsPanel* DatasetPanel::getSubjectsPanel(){
    return ui->subjectsPanel;
}


ExecutePanel* DatasetPanel::getExecutePanel(){
    return ui->executePanel;
}
