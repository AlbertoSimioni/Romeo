#include "newalgorithmdialog.h"
#include "ui_newalgorithmdialog.h"
#include <QFileDialog>
#include <QDir>
#include <QLibrary>
#include <vector>
#include <QMessageBox>
using namespace romeo::view::dialogs;
using namespace romeo::model::protocols::algorithms;
using namespace std;
NewAlgorithmDialog::NewAlgorithmDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewAlgorithmDialog)
{
    ui->setupUi(this);
    ui->errorLabel->setHidden(true);
    ui->okCancel->button(QDialogButtonBox::Ok)->setEnabled(false);
    connectUI();
}

void NewAlgorithmDialog::connectUI(){
    connect(ui->browseButton,SIGNAL(clicked()),this,SLOT(openBrowseDialog()));
    connect(ui->algorithmLineEdit,SIGNAL(textChanged(QString)),this,SIGNAL(nameChanged(QString)));
    connect(ui->algorithmLineEdit,SIGNAL(textChanged(QString)),this,SLOT(checkForm()));
    connect(ui->functionName,SIGNAL(textChanged(QString)),this,SLOT(checkForm()));
    connect(ui->pathLineEdit,SIGNAL(textChanged(QString)),this,SLOT(checkForm()));
    connect(ui->addParameterButton,SIGNAL(clicked()),this,SLOT(addButtonClicked()));
    connect(ui->okCancel,SIGNAL(rejected()),this,SLOT(reject()));
    connect(ui->okCancel->button(QDialogButtonBox::Ok),SIGNAL(clicked()),this,SLOT(okButtonClicked()));

}

NewAlgorithmDialog::~NewAlgorithmDialog()
{
    delete ui;
}


void NewAlgorithmDialog::showErrorName(bool show)
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


void NewAlgorithmDialog::openBrowseDialog(){
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Select dynamic library"), QDir::home().path(), tr("Dynamic library files (*.so *.dll *.dylib)"));
    if(!fileName.isNull())
        ui->pathLineEdit->setText(fileName);
}


void NewAlgorithmDialog::resetForms(){
    ui->pathLineEdit->clear();
    ui->functionName->clear();
    ui->algorithmLineEdit->clear();
    ui->descriptionText->clear();
    ui->errorLabel->setHidden(true);
    while(!(parameters.isEmpty()))
        delete parameters.takeFirst();
}


void NewAlgorithmDialog::reject(){
    resetForms();
    QDialog::reject();
}


void NewAlgorithmDialog::checkForm(){
    bool valid = true;
    if(ui->algorithmLineEdit->text().isEmpty()  || ui->functionName->text().isEmpty() || ui->pathLineEdit->text().isEmpty())
        valid = false;

    for(int i = 0; i< parameters.size() && valid; i++){
        valid = parameters[i]->isValid();
    }

    if(!valid)ui->okCancel->button(QDialogButtonBox::Ok)->setEnabled(false);

    else if(ui->errorLabel->isHidden())ui->okCancel->button(QDialogButtonBox::Ok)->setEnabled(true);
}

void NewAlgorithmDialog::addButtonClicked(){
    NewAlgorithmParameterForm* param = new NewAlgorithmParameterForm(this);
    parameters.append(param);
    ui->parametersLayout->addWidget(param);
    connect(param,SIGNAL(valueEntered()),this,SLOT(checkForm()));
    connect(param,SIGNAL(deletePressed(NewAlgorithmParameterForm*)),this,SLOT(deleteButtonClicked(NewAlgorithmParameterForm*)));
    checkForm();
}


void NewAlgorithmDialog::deleteButtonClicked(NewAlgorithmParameterForm* param){
    int i =parameters.indexOf(param);
    delete parameters.takeAt(i);
    checkForm();
}


void NewAlgorithmDialog::okButtonClicked(){
    QString name = ui->algorithmLineEdit->text();
    QString desc = ui->descriptionText->document()->toPlainText();
    QString dyfn = ui->functionName->text();
    QString dylp = ui->pathLineEdit->text();
    QList<AbstractAlgorithm::AlgorithmParameter> newAlgorithmParameters;
    for(int i = 0; i<parameters.size();i++){
        NewAlgorithmParameterForm* param = parameters[i];
        QString parameterName = param->getName();
        QString defaultParameter = param->getDefault();
        AbstractAlgorithm::ParameterType type = param->getType();
        newAlgorithmParameters.append(AbstractAlgorithm::AlgorithmParameter(parameterName,type,defaultParameter));
    }

    typedef void (*MyPrototype)(double** data, int* mask, int nrows, int ncols,int* clusterid, vector<string> parameters);
    MyPrototype myFunction =
            (MyPrototype) QLibrary::resolve(dylp, dyfn.toStdString().c_str());
    if (!myFunction){
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.setText("Can't load the dynamic library!");
        msgBox.exec();
    }
    else{
        QDir currentDir = QDir(QDir::currentPath());
        if(currentDir.cd("algorithms")){}
        else{
            currentDir.mkdir("algorithms");
            currentDir.cd("algorithms");
        }
        QString newFilePath = currentDir.path() +"/" +name+"."+ (dylp.split(".").takeLast()) ;
        newFilePath = QDir::toNativeSeparators(newFilePath);
        newFilePath = QUrl::fromLocalFile(newFilePath.replace(" ","\ ")).path();
        QFile::copy(dylp, newFilePath);

    resetForms();
    emit createAlgorithm(name,desc,dyfn,dylp,newAlgorithmParameters);
    accept();
    }
}
