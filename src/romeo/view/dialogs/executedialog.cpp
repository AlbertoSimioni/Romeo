#include "executedialog.h"
#include "ui_executedialog.h"

ExecuteDialog::ExecuteDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ExecuteDialog)
{
    ui->setupUi(this);
}

ExecuteDialog::~ExecuteDialog()
{
    delete ui;
}
