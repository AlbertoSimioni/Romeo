#include "parametervalueform.h"
#include "ui_parametervalueform.h"
using namespace romeo::view::dialogs;
using namespace romeo::model::protocols::algorithms;
ParameterValueForm::ParameterValueForm(AbstractAlgorithm::AlgorithmParameter parameter,QWidget *parent) :
    QWidget(parent), validValue(false),
    ui(new Ui::ParameterValueForm)
{
    ui->setupUi(this);

    ui->nameLabel->setText(parameter.getName());
    type = parameter.getType();
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
    ui->valueLineEdit->setText(parameter.getDefaultParameter());
    checkValidity(parameter.getDefaultParameter());

    connect(ui->valueLineEdit,SIGNAL(textChanged(QString)),this,SLOT(checkValidity(QString)));
}


ParameterValueForm::~ParameterValueForm()
{
    delete ui;
}


QString ParameterValueForm::getName()
{
    return ui->nameLabel->text();
}


AbstractAlgorithm::ParameterType ParameterValueForm::getType()
{
    return type;
}


QString ParameterValueForm::getValue()
{
    return ui->valueLineEdit->text();
}


AbstractAlgorithm::AlgorithmParameter ParameterValueForm::getParameter()
{
    return AbstractAlgorithm::AlgorithmParameter(ui->nameLabel->text(),type,ui->valueLineEdit->text());
}


void ParameterValueForm::checkValidity(QString value)
{
    bool valid = true;
    switch(type){

    case AbstractAlgorithm::CHAR: if(value.length() != 1) valid = false;
        break;
    case AbstractAlgorithm::BOOL: if((value != "TRUE") && (value != "FALSE")) valid = false;
        break;
    case AbstractAlgorithm::DOUBLE: value.toDouble(&valid);
        break;
    case AbstractAlgorithm::INT: value.toInt(&valid);
        break;
    }
    validValue = valid;
    QPalette palette = ui->valueLineEdit->palette();

    if(!validValue) palette.setColor(QPalette::Text,QColor(255,0,0));
    else  palette.setColor(QPalette::Text,QColor(0,0,0));

    ui->valueLineEdit->setPalette(palette);
    emit valueEntered(valid);
}


bool ParameterValueForm::isValid() const
{
    return validValue;
}


