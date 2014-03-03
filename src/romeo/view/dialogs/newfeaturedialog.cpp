#include "newfeaturedialog.h"
#include "ui_newfeaturedialog.h"

#include<QFileDialog>
#include <QDir>
#include<QMessageBox>
#include<QLibrary>
using namespace romeo::view::dialogs;
using namespace romeo::model::protocols::features;
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
    connect(ui->okCancel->button(QDialogButtonBox::Ok),SIGNAL(clicked()),this,SLOT(okButtonClicked()));
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



void NewFeatureDialog::okButtonClicked(){
    QString name = ui->featureLineEdit->text();
    QString desc = ui->descriptionText->document()->toPlainText();
    QString dyfn = ui->functionLineEdit->text();
    QString dylp = ui->pathLineEdit->text();
    QString typeName = ui->comboBox->currentText();
    FeatureType type;

    bool loaded = false;

    if(typeName == "Static First Order"){
        type = FIRSTORDER;
        typedef int (*MyPrototype)(int* data,int size,int dimesion);
        MyPrototype myFunction =
                (MyPrototype) QLibrary::resolve(dylp, dyfn.toStdString().c_str());
        if (myFunction){
            loaded = true;
        }
    }
    if(typeName == "Static Second Order"){
        type = SECONDORDER;
        typedef double (*MyPrototype)(int data[256][256] );
        MyPrototype myFunction =
                (MyPrototype) QLibrary::resolve(dylp, dyfn.toStdString().c_str());
        if (myFunction){
            loaded = true;
        }
    }

    if(typeName == "Dynamic"){
        type = DYNAMIC;
        typedef double* (*MyPrototype)(int**data, const int numberOfPixel, int begin, int end);
        MyPrototype myFunction =
                (MyPrototype) QLibrary::resolve(dylp, dyfn.toStdString().c_str());
        if (myFunction){
            loaded = true;
        }
    }

    if(!loaded){
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.setText("Can't load the dynamic library!");
        msgBox.exec();
    }

    else{
        QDir currentDir = QDir(QDir::currentPath());
        if(currentDir.cd("features")){}
        else{
            currentDir.mkdir("features");
            currentDir.cd("features");
        }
        QString newFilePath = currentDir.path() +"/" +name+"."+ (dylp.split(".").takeLast()) ;
        QFile::copy(dylp, newFilePath);
        resetForms();
        emit createFeature(name,desc,dyfn,newFilePath,type);
        accept();
    }
}
