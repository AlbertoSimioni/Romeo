#include "datasetpanel.h"
#include "ui_datasetpanel.h"
using namespace romeo::view::mainWindow;
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
