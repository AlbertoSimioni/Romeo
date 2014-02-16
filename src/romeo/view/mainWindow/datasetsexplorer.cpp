#include "datasetsexplorer.h"
#include "ui_datasetsexplorer.h"

DatasetsExplorer::DatasetsExplorer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DatasetsExplorer)
{
    ui->setupUi(this);
}

DatasetsExplorer::~DatasetsExplorer()
{
    delete ui;
}
