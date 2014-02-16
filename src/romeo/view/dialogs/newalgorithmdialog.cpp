#include "newalgorithmdialog.h"
#include "ui_newalgorithmdialog.h"

NewAlgorithmDialog::NewAlgorithmDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewAlgorithmDialog)
{
    ui->setupUi(this);
}

NewAlgorithmDialog::~NewAlgorithmDialog()
{
    delete ui;
}
