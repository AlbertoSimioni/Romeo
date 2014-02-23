#include "newfeaturedialog.h"
#include "ui_newfeaturedialog.h"
#include<QFileDialog>
#include <QDir>

using namespace romeo::view::dialogs;
NewFeatureDialog::NewFeatureDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewFeatureDialog)
{
    ui->setupUi(this);

    ui->errorLabel->setHidden(true);
    ui->okCancel->button(QDialogButtonBox::Ok)->setEnabled(false);
    connectUI();
}

NewFeatureDialog::~NewFeatureDialog()
{
    delete ui;
}



void NewFeatureDialog::connectUI(){
    connect(ui->browseButton,SIGNAL(clicked()),this,SLOT(openBrowseDialog()));
    connect(ui->featureLineEdit,SIGNAL(textChanged(QString)),this,SIGNAL(nameChanged(QString)));
    connect(ui->featureLineEdit,SIGNAL(textChanged(QString)),this,SLOT(checkForm()));
    connect(ui->functionLineEdit,SIGNAL(textChanged(QString)),this,SLOT(checkForm()));
    connect(ui->pathLineEdit,SIGNAL(textChanged(QString)),this,SLOT(checkForm()));
    connect(ui->okCancel,SIGNAL(rejected()),this,SLOT(reject()));
}



void NewFeatureDialog::showErrorName(bool show)
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


void NewFeatureDialog::openBrowseDialog(){
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Select dynamic library"), QDir::home().path(), tr("Dynamic library files (*.so *.dll *.dylib)"));
    if(!fileName.isNull())
        ui->pathLineEdit->setText(fileName);
}


void NewFeatureDialog::resetForms(){
    ui->pathLineEdit->clear();
    ui->functionLineEdit->clear();
    ui->featureLineEdit->clear();
    ui->descriptionText->clear();
    ui->errorLabel->setHidden(true);

}


void NewFeatureDialog::reject(){
    resetForms();
    QDialog::reject();
}

void NewFeatureDialog::checkForm(){
    bool valid = true;
    if(ui->featureLineEdit->text().isEmpty()  || ui->functionLineEdit->text().isEmpty() || ui->pathLineEdit->text().isEmpty())
        valid = false;


    if(!valid)ui->okCancel->button(QDialogButtonBox::Ok)->setEnabled(false);

    else if(ui->errorLabel->isHidden())ui->okCancel->button(QDialogButtonBox::Ok)->setEnabled(true);
}
