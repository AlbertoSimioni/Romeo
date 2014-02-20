#include "newdatasetdialog.h"
#include "ui_newdatasetdialog.h"
using namespace romeo::view::dialogs;
NewDatasetDialog::NewDatasetDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewDatasetDialog)
{
    ui->setupUi(this);
}

NewDatasetDialog::~NewDatasetDialog()
{
    delete ui;
}
