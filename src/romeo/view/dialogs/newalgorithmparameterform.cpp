#include "newalgorithmparameterform.h"
#include "ui_newalgorithmparameterform.h"
using namespace romeo::view::dialogs;
using namespace romeo::model::protocols::algorithms;


NewAlgorithmParameterForm::NewAlgorithmParameterForm(QWidget *parent) :
    QWidget(parent), valid(false),
    ui(new Ui::NewAlgorithmParameterForm)
{
    ui->setupUi(this);
    connect(ui->deleteButton,SIGNAL(clicked()),this,SLOT(onDeleteClicked()));
    connect(ui->defaultLineEdit,SIGNAL(textChanged(QString)),this,SLOT(checkValidity()));
    connect(ui->valueLineEdit,SIGNAL(textChanged(QString)),this,SLOT(checkValidity()));
    connect(ui->typeCombo,SIGNAL(currentIndexChanged(int)),this,SLOT(checkValidity()));
}


NewAlgorithmParameterForm::~NewAlgorithmParameterForm()
{
    delete ui;
}



void NewAlgorithmParameterForm::checkValidity(){
    bool empty = false;
    bool validDefault = true;

    empty = ui->valueLineEdit->text().isEmpty();

    QString type = ui->typeCombo->currentText();
    QString defValue = ui->defaultLineEdit->text();


    if(type == "Integer")  defValue.toInt(&validDefault);
    if(type == "Double") defValue.toDouble(&validDefault);
    if(type == "Boolean") if((defValue != "TRUE") && (defValue != "FALSE")) validDefault = false;
    if(type == "Char") if(defValue.length() != 1) validDefault = false;


    valid = !empty && (validDefault);
    QPalette palette = ui->defaultLineEdit->palette();

    if(!validDefault) palette.setColor(QPalette::Text,QColor(255,0,0));
    else  palette.setColor(QPalette::Text,QColor(0,0,0));

    ui->defaultLineEdit->setPalette(palette);

    emit valueEntered();
}



QString NewAlgorithmParameterForm::getName(){
    return ui->valueLineEdit->text();
}

AbstractAlgorithm::ParameterType NewAlgorithmParameterForm::getType(){
    QString type = ui->typeCombo->currentText();
    if(type == "Integer")  return AbstractAlgorithm::INT;
    if(type == "Double") return AbstractAlgorithm::DOUBLE;
    if(type == "Boolean") return AbstractAlgorithm::BOOL;
    if(type == "Char") return AbstractAlgorithm::CHAR;
}



QString NewAlgorithmParameterForm::getDefault(){
    return ui->defaultLineEdit->text();
}


bool NewAlgorithmParameterForm::isValid(){
    return valid;
}

void NewAlgorithmParameterForm::onDeleteClicked(){
    emit deletePressed(this);
}
