#include "protocoldialog.h"
#include "ui_protocoldialog.h"
#include <QList>

using namespace romeo::model::protocols::algorithms;
using namespace romeo::view::dialogs;
using namespace romeo::model::protocols::features;


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
    ui->next1->setEnabled(false);
    fillAlgorithmsCombo();
    fillFeaturesList();
    changeParametersForm();
    connectUI();

}


void ProtocolDialog::connectUI(){

    connect(ui->next1,SIGNAL(clicked()),this,SLOT(nextStep()));
    connect(ui->next2,SIGNAL(clicked()),this,SLOT(nextStep()));
    connect(ui->back2,SIGNAL(clicked()),this,SLOT(previousStep()));
    connect(ui->back3,SIGNAL(clicked()),this,SLOT(previousStep()));
    connect(ui->protocolLineEdit,SIGNAL(textChanged(QString)),this,SIGNAL(nameChanged(QString)));
    connect(ui->protocolLineEdit,SIGNAL(textChanged(QString)),this,SLOT(checkEmpty(QString)));
    connect(ui->featuresList,SIGNAL(itemDoubleClicked(QListWidgetItem*)),this,SLOT(addFeature(QListWidgetItem*)));
    connect(ui->addButton,SIGNAL(clicked()),this,SLOT(addButtonClicked()));
    connect(ui->removeButton,SIGNAL(clicked()),this,SLOT(removeButtonClicked()));
    connect(ui->protocolFeaturesList,SIGNAL(itemDoubleClicked(QListWidgetItem*)),this,SLOT(removeFeature(QListWidgetItem*)));
    connect(ui->cancel1,SIGNAL(clicked()),this,SLOT(reject()));
    connect(ui->cancel2,SIGNAL(clicked()),this,SLOT(reject()));
    connect(ui->cancel3,SIGNAL(clicked()),this,SLOT(reject()));
    connect(ui->AlgorithmCombo,SIGNAL(currentIndexChanged(int)),this,SLOT(changeParametersForm()));
    connect(ui->dataTypeCombo,SIGNAL(currentIndexChanged(QString)),this,SLOT(fillFeaturesList()));

}


ProtocolDialog::~ProtocolDialog()
{
    delete ui;
}


void ProtocolDialog::showErrorName(bool show)
{
    if(!show){
        ui->errorLabel->setHidden(true);
        ui->next1->setEnabled(true);
    }
    else{
        ui->errorLabel->setHidden(false);
        ui->next1->setEnabled(false);
    }
}


void ProtocolDialog::nextStep()
{
   int currentIndex = ui->Wizard->currentIndex();
   if(currentIndex < 2)
       ui->Wizard->setCurrentIndex(currentIndex+1);
}



void ProtocolDialog::previousStep()
{
       int currentIndex = ui->Wizard->currentIndex();
       if(currentIndex > 0)
           ui->Wizard->setCurrentIndex(currentIndex-1);
}



void ProtocolDialog::addFeature(QListWidgetItem *item)
{
    bool stop = false;
    for(int i =0; i< (ui->protocolFeaturesList->count()) && (!stop);i++){
        if(ui->protocolFeaturesList->item(i)->text() == item->text())
            stop = true;
    }
    if(!stop)
        ui->protocolFeaturesList->addItem(item->clone());
}



void ProtocolDialog::removeFeature(QListWidgetItem *item)
{
    delete item;
}



void ProtocolDialog::addButtonClicked()
{
    QList<QListWidgetItem*> selected = ui->featuresList->selectedItems();
    if(!selected.isEmpty())
        addFeature(selected.at(0));
}



void ProtocolDialog::removeButtonClicked(){
    QList<QListWidgetItem*> selected = ui->protocolFeaturesList->selectedItems();

    if(!selected.isEmpty())
        removeFeature(selected.at(0));
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
    ui->featuresList->clear();
    ui->protocolFeaturesList->clear();
    QList<AbstractFeature*> features = featuresList->getFeaturesList();
    QString type = ui->dataTypeCombo->currentText();

    if(type == "Static"){
        for(int i = 0; i< features.size();i++){
            AbstractFeature* feature = features[i];
            if((feature->getType() == FIRSTORDER) || (feature->getType() == SECONDORDER))
                ui->featuresList->addItem(feature->getName());
        }
    }

    if(type == "Dynamic"){
        for(int i = 0; i< features.size();i++){
            AbstractFeature* feature = features[i];
            if((feature->getType() == DYNAMIC))
                ui->featuresList->addItem(feature->getName());
        }
    }

}



void ProtocolDialog::fillAlgorithmsCombo(){
    ui->AlgorithmCombo->clear();
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
        connect(parameterForm,SIGNAL(valueEntered(bool)),this,SLOT(checkParametersValidity()));
        ui->parameterLayout->addWidget(parameterForm);

        parameters.append(parameterForm);
    }
    }
    checkParametersValidity();
}


void ProtocolDialog::checkParametersValidity(){
    bool stop = false;
    for(int i = 0; i< parameters.size() && !stop; i++){
        if(!(parameters[i]->isValid())) stop = true;
    }
    if(stop) ui->finish3->setEnabled(false);
    else ui->finish3->setEnabled(true);
}


void ProtocolDialog::checkEmpty(QString name){
    if(name.isEmpty()) ui->next1->setEnabled(false);
}
