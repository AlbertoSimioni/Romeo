/**
* \file addsubjectdialog.cpp
* \author Alessandro Strenghetto
* \date 2014-02-17
**
* \brief Header della classe AddSubjectDialog del package romeo::view::dialogs
*/

#include "addsubjectdialog.h"
#include "ui_addsubjectdialog.h"
#include <QFileDialog>
using namespace romeo::view::dialogs;
using namespace romeo::model;
AddSubjectDialog::AddSubjectDialog(QWidget *parent) :
    QDialog(parent), currentInputFormat(TYPE2D),
    ui(new Ui::AddSubjectDialog)
{
    ui->setupUi(this);

    ui->errorLabel->setHidden(true);
    ui->okCancel->button(QDialogButtonBox::Ok)->setEnabled(false);
    connectUI();
    changeFilters();
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
    connect(ui->okCancel->button(QDialogButtonBox::Ok),SIGNAL(clicked()),this,SLOT(okButtonClicked()));
    connect(ui->browseDataButton,SIGNAL(clicked()),this,SLOT(openBrowseDataDialog()));
    connect(ui->browseMaskButton_2,SIGNAL(clicked()),this,SLOT(openBrowseMaskDialog()));
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


void AddSubjectDialog::setCurrentInputFormat(const romeo::model::InputFormat &value)
{
    currentInputFormat = value;
    changeFilters();
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


void AddSubjectDialog::okButtonClicked(){
    QString name = ui->nameLineEdit->text();
    QString dataPath = ui->pathDataLineEdit->text();
    QString maskPath = ui->pathMaskLineEdit->text();
    resetForms();
    emit createNewSubject(name,dataPath,maskPath);
    reject();
}


void AddSubjectDialog::changeFilters(){

    switch(currentInputFormat){
    case TYPE2D:
        currentFiltersData = "Image 2D (*.jpg *.png *.bmp *.tiff *.tif)";
        currentFiltersMask = "Image 2D (*.jpg *.png *.bmp *.tiff *.tif)";

        break;
    case TYPE2DT:
        currentFiltersData = "Video 2D (*.avi)";
        currentFiltersMask = "Image 2D (*.jpg *.png *.bmp *.tiff *.tif)";
        break;
    case TYPE3D:
        currentFiltersData = "Image 3D (*.hdr *.nii )";
        currentFiltersMask = "Image 3D (*.hdr *.nii )";
        break;
    case TYPE3DT:
        currentFiltersData = "Images 3DT (*.hdr *.nii )";
        currentFiltersMask = "Image 3D (*.hdr *.nii )";
        break;
    }
}



void AddSubjectDialog::openBrowseMaskDialog(){
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Select Mask"), QDir::home().path(), currentFiltersMask);
    if(!fileName.isNull())
        ui->pathMaskLineEdit->setText(fileName);
}


void AddSubjectDialog::openBrowseDataDialog(){
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Select Data"), QDir::home().path(), currentFiltersData);
    if(!fileName.isNull())
        ui->pathDataLineEdit->setText(fileName);
}
