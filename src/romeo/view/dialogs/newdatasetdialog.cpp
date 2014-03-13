/**
* \file newdatasetdialog.cpp
* \author Alessandro Strenghetto
* \date 2014-02-17
**
* \brief Header della classe NewDatasetDialog del package romeo::view::dialogs
*/


#include "newdatasetdialog.h"
#include "ui_newdatasetdialog.h"
#include <QPushButton>
using namespace romeo::view::dialogs;
using namespace romeo::model;
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
    connect(ui->okCancel->button(QDialogButtonBox::Ok),SIGNAL(clicked()),this,SLOT(okButtonClicked()));
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


void NewDatasetDialog::okButtonClicked(){

    QString name = ui->nameLineEdit->text();
    QString typeName = ui->typeCombo->currentText();
    InputFormat type;
    if(typeName == "2D") type = TYPE2D;
    if(typeName == "2D-t") type = TYPE2DT;
    if(typeName == "3D") type = TYPE3D;
    if(typeName == "3D-t") type = TYPE3DT;

    resetForms();
    emit createDataset(name,type);
    accept();
}
