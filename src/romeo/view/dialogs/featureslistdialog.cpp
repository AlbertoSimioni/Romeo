#include "featureslistdialog.h"
#include "ui_featureslistdialog.h"

FeaturesListDialog::FeaturesListDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FeaturesListDialog)
{
    ui->setupUi(this);
}

FeaturesListDialog::~FeaturesListDialog()
{
    delete ui;
}
