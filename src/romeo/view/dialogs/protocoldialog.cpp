#include "protocoldialog.h"
#include "ui_protocoldialog.h"
using namespace romeo::view::dialogs;
ProtocolDialog::ProtocolDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ProtocolDialog)
{
    ui->setupUi(this);
    ui->errorLabel->setHidden(true);
    ui->Wizard->setCurrentIndex(0);
   // connect(ui)


}

ProtocolDialog::~ProtocolDialog()
{
    delete ui;
}

void ProtocolDialog::showErrorName(bool flag){
    ui->errorLabel->setHidden(flag);
}


void ProtocolDialog::nextStep(){
   // ui->Wizard->
}
