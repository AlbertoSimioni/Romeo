#include "newalgorithmparameterform.h"
#include "ui_newalgorithmparameterform.h"
using namespace romeo::view::dialogs;
NewAlgorithmParameterForm::NewAlgorithmParameterForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NewAlgorithmParameterForm)
{
    ui->setupUi(this);
}

NewAlgorithmParameterForm::~NewAlgorithmParameterForm()
{
    delete ui;
}
