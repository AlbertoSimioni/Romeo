#include "newdatasetdialog.h"
#include "ui_newdatasetdialog.h"
#include <QPushButton>
using namespace romeo::view::dialogs;
NewDatasetDialog::NewDatasetDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewDatasetDialog)
{
    ui->setupUi(this);
    ui->ErrorLabel->setHidden(true);
    ui->okCancel->button(QDialogButtonBox::Ok)->setEnabled(false);
    connectUI();

}

NewDatasetDialog::~NewDatasetDialog()
{
    delete ui;
}


void NewDatasetDialog::connectUI(){

    connect(ui->nameLineEdit,SIGNAL(textChanged(QString)),this,SIGNAL(nameChanged(QString)));
    connect(ui->nameLineEdit,SIGNAL(textChanged(QString)),this,SLOT(checkForm()));
    connect(ui->okCancel,SIGNAL(rejected()),this,SLOT(reject()));
}



void NewDatasetDialog::showErrorName(bool show)
{
    if(!show){
        ui->ErrorLabel->setHidden(true);
        ui->okCancel->button(QDialogButtonBox::Ok)->setEnabled(true);
    }
    else{
        ui->ErrorLabel->setHidden(false);
        ui->okCancel->button(QDialogButtonBox::Ok)->setEnabled(false);
    }
}


void NewDatasetDialog::resetForms(){
    ui->nameLineEdit->clear();
    ui->ErrorLabel->setHidden(true);

}


void NewDatasetDialog::reject(){
    resetForms();
    QDialog::reject();
}

void NewDatasetDialog::checkForm(){
    bool valid = true;
    if(ui->nameLineEdit->text().isEmpty())
        valid = false;


    if(!valid)ui->okCancel->button(QDialogButtonBox::Ok)->setEnabled(false);

    else if(ui->ErrorLabel->isHidden())ui->okCancel->button(QDialogButtonBox::Ok)->setEnabled(true);
}
