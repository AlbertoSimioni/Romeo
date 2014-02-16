#include "datasetpanel.h"
#include "ui_datasetpanel.h"

DatasetPanel::DatasetPanel(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DatasetPanel)
{
    ui->setupUi(this);
}

DatasetPanel::~DatasetPanel()
{
    delete ui;
}
