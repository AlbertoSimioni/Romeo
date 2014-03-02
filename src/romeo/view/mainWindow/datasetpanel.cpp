#include "datasetpanel.h"
#include "ui_datasetpanel.h"
using namespace romeo::view::mainWindow;
using namespace romeo::model::datasets;
DatasetPanel::DatasetPanel(QWidget *parent) :
    QWidget(parent),currentDataset(0),
    ui(new Ui::DatasetPanel)
{
    ui->setupUi(this);

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
    currentDataset = dataset;
    if(currentDataset != 0){
        ui->datasetLabel->setText(currentDataset->getName());
    }
    else{
        ui->datasetLabel->setText("No Dataset");
    }
    ui->protocolsPanel->setCurrentDataset(currentDataset);
    ui->subjectsPanel->setCurrentDataset(currentDataset);
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
