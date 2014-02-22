#include "parametervalueform.h"
#include "ui_parametervalueform.h"
using namespace romeo::view::dialogs;
using namespace romeo::model::protocols::algorithms;
ParameterValueForm::ParameterValueForm(AbstractAlgorithm::AlgorithmParameter* parameter,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ParameterValueForm)
{
    ui->nameLabel->setText(parameter->getName());
    type = parameter->getType();
    QString stringType = QString();
    if(type == AbstractAlgorithm::BOOL)
        stringType = "Boolean";
    if(type == AbstractAlgorithm::CHAR)
        stringType = "Char";
    if(type == AbstractAlgorithm::DOUBLE)
        stringType = "Double";
    if(type == AbstractAlgorithm::INT)
        stringType = "Integer";

    ui->typeLabel->setText(stringType);
    ui->valueLineEdit->setText(parameter->getDefaultParameter());
    ui->setupUi(this);
}

ParameterValueForm::~ParameterValueForm()
{
    delete ui;
}

QString ParameterValueForm::getName(){
    return ui->nameLabel->text();
}


AbstractAlgorithm::ParameterType ParameterValueForm::getType(){
    return type;
}


QString ParameterValueForm::getValue(){
    return ui->valueLineEdit->text();
}

void ParameterValueForm::checkValidity(QString value){

}
