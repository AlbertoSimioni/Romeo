#include "protocoldialog.h"
#include "ui_protocoldialog.h"
#include <QList>

using namespace romeo::model::protocols::algorithms;
using namespace romeo::view::dialogs;


ProtocolDialog::ProtocolDialog(
        model::protocols::algorithms::AlgorithmsList *al,
        model::protocols::features::FeaturesList *fl,
        QWidget *parent) :
        QDialog(parent),
        featuresList(fl),
        algorithmsList(al),
        ui(new Ui::ProtocolDialog)
{
    ui->setupUi(this);
    ui->errorLabel->setHidden(true);
    ui->Wizard->setCurrentIndex(0);
    fillAlgorithmsCombo();
    changeParametersForm();
    connectUI();

}


void ProtocolDialog::connectUI(){

    connect(ui->next1,SIGNAL(clicked()),this,SLOT(nextStep()));
    connect(ui->next2,SIGNAL(clicked()),this,SLOT(nextStep()));
    connect(ui->back2,SIGNAL(clicked()),this,SLOT(previousStep()));
    connect(ui->back3,SIGNAL(clicked()),this,SLOT(previousStep()));
    connect(ui->protocolLineEdit,SIGNAL(textChanged(QString)),this,SIGNAL(nameChanged(QString)));
    connect(ui->featuresList,SIGNAL(itemDoubleClicked(QListWidgetItem*)),this,SLOT(addFeature(QListWidgetItem*)));
    connect(ui->addButton,SIGNAL(clicked()),this,SLOT(addButtonClicked()));
    connect(ui->removeButton,SIGNAL(clicked()),this,SLOT(removeButtonClicked()));
    connect(ui->protocolFeaturesList,SIGNAL(itemDoubleClicked(QListWidgetItem*)),this,SLOT(removeFeature(QListWidgetItem*)));
    connect(ui->cancel1,SIGNAL(clicked()),this,SLOT(reject()));
    connect(ui->cancel2,SIGNAL(clicked()),this,SLOT(reject()));
    connect(ui->cancel3,SIGNAL(clicked()),this,SLOT(reject()));

}


ProtocolDialog::~ProtocolDialog()
{
    delete ui;
}

void ProtocolDialog::showErrorName(bool show){
    if(!show){
        ui->errorLabel->setHidden(true);
        ui->next1->setEnabled(true);
    }
    else{
        ui->errorLabel->setHidden(false);
        ui->next1->setEnabled(false);
    }
}


void ProtocolDialog::nextStep(){
   int currentIndex = ui->Wizard->currentIndex();
   if(currentIndex < 2)
       ui->Wizard->setCurrentIndex(currentIndex+1);
}



void ProtocolDialog::previousStep(){
       int currentIndex = ui->Wizard->currentIndex();
       if(currentIndex > 0)
           ui->Wizard->setCurrentIndex(currentIndex-1);
}



void ProtocolDialog::addFeature(QListWidgetItem *item){
    bool stop = false;
    for(int i =0; i< (ui->protocolFeaturesList->count()) && (!stop);i++){
        if(ui->protocolFeaturesList->item(i)->text() == item->text())
            stop = true;
    }
    if(!stop)
        ui->protocolFeaturesList->addItem(item->clone());
}



void ProtocolDialog::removeFeature(QListWidgetItem *item){
    delete item;
}



void ProtocolDialog::addButtonClicked(){
    addFeature(ui->featuresList->selectedItems().at(0));
}




void ProtocolDialog::removeButtonClicked(){
    removeFeature(ui->protocolFeaturesList->selectedItems().at(0));
}




void ProtocolDialog::resetForms(){
     ui->errorLabel->setHidden(true);
     ui->protocolLineEdit->clear();
     ui->Wizard->setCurrentIndex(0);
     ui->protocolFeaturesList->clear();

}



void ProtocolDialog::reject(){
    resetForms();
    return QDialog::reject();
}



void ProtocolDialog::fillFeaturesList(){

}


void ProtocolDialog::fillAlgorithmsCombo(){
    QList<AbstractAlgorithm*> algorithms = algorithmsList->getAlgorithmsList();
    for(int i = 0; i < algorithms.size(); i++){
        ui->AlgorithmCombo->addItem(algorithms[i]->getName());
    }
}




void ProtocolDialog::changeParametersForm(){

    while(!parameters.isEmpty()){
        delete parameters.takeFirst();
    }

    AbstractAlgorithm* algorithm= algorithmsList->getAlgorithm(ui->AlgorithmCombo->currentText());
    if(algorithm){
    QList<AbstractAlgorithm::AlgorithmParameter> param = algorithm->getParameters();
    while(!(param.isEmpty())){
        ParameterValueForm* parameterForm = new ParameterValueForm(param.takeFirst(),this);
        ui->parameterLayout->addWidget(parameterForm);

        parameters.append(parameterForm);
    }
    }
}
