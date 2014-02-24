#include "addsubjectdialog.h"
#include "ui_addsubjectdialog.h"
using namespace romeo::view::dialogs;

AddSubjectDialog::AddSubjectDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddSubjectDialog)
{
    ui->setupUi(this);

    ui->errorLabel->setHidden(true);
    ui->okCancel->button(QDialogButtonBox::Ok)->setEnabled(false);
    connectUI();
}

AddSubjectDialog::~AddSubjectDialog()
{
    delete ui;
}

void AddSubjectDialog::connectUI(){

    connect(ui->nameLineEdit,SIGNAL(textChanged(QString)),this,SIGNAL(nameChanged(QString)));
    connect(ui->nameLineEdit,SIGNAL(textChanged(QString)),this,SLOT(checkForm()));
    connect(ui->pathDataLineEdit,SIGNAL(textChanged(QString)),this,SLOT(checkForm()));
    connect(ui->pathMaskLineEdit,SIGNAL(textChanged(QString)),this,SLOT(checkForm()));
    connect(ui->okCancel,SIGNAL(rejected()),this,SLOT(reject()));
}



void AddSubjectDialog::showErrorName(bool show)
{
    if(!show){
        ui->errorLabel->setHidden(true);
        ui->okCancel->button(QDialogButtonBox::Ok)->setEnabled(true);
    }
    else{
        ui->errorLabel->setHidden(false);
        ui->okCancel->button(QDialogButtonBox::Ok)->setEnabled(false);
    }
}


void AddSubjectDialog::resetForms(){
    ui->nameLineEdit->clear();
    ui->pathDataLineEdit->clear();
    ui->pathMaskLineEdit->clear();
    ui->errorLabel->setHidden(true);

}


void AddSubjectDialog::reject(){
    resetForms();
    QDialog::reject();
}

void AddSubjectDialog::checkForm(){
    bool valid = true;
    if(ui->nameLineEdit->text().isEmpty() || ui->pathDataLineEdit->text().isEmpty())
        valid = false;


    if(!valid)ui->okCancel->button(QDialogButtonBox::Ok)->setEnabled(false);

    else if(ui->errorLabel->isHidden())ui->okCancel->button(QDialogButtonBox::Ok)->setEnabled(true);
}
