/**
* \file algorithmslistdialog.cpp
* \author Alessandro Strenghetto
* \date 2014-02-17
**
* \brief Header della classe AlgorithmsListDialog del package romeo::view::dialogs
*/


#include "algorithmslistdialog.h"
#include "ui_algorithmslistdialog.h"
using namespace romeo::view::dialogs;
using namespace romeo::model::protocols::algorithms;
AlgorithmsListDialog::AlgorithmsListDialog(AlgorithmsList* al,  QWidget *parent) :
    QDialog(parent), algorithms(al),
    ui(new Ui::AlgorithmsListDialog)
{
    ui->setupUi(this);
    connectUI();
    fillAlgorithmsList();
}

AlgorithmsListDialog::~AlgorithmsListDialog()
{
    delete ui;
}


void AlgorithmsListDialog::connectUI(){
    connect(ui->okButton,SIGNAL(clicked()),this,SLOT(accept()));
    connect(algorithms,SIGNAL(algorithmsListModified()),this,SLOT(fillAlgorithmsList()));
    connect(ui->algorithmsTable,SIGNAL(itemSelectionChanged()),this,SLOT(showDescription()));
}


void AlgorithmsListDialog::fillAlgorithmsList(){
    ui->algorithmsTable->clear();
    ui->descriptionText->clear();

    QList<AbstractAlgorithm*> algs =algorithms->getAlgorithmsList();

    for(int i = 0; i< algs.size();i++){
        QTreeWidgetItem *itm =new QTreeWidgetItem(ui->algorithmsTable);
        itm->setText(0,algs[i]->getName());
    }
}

void AlgorithmsListDialog::showDescription(){

    QList<QTreeWidgetItem*> selected =  ui->algorithmsTable->selectedItems();
    if(!selected.isEmpty()){
        QString algName =  selected.at(0)->data(0,Qt::EditRole).toString();
        AbstractAlgorithm* algorithm =algorithms->getAlgorithm(algName);
        ui->descriptionText->setText(algorithm->getDescription());
    }


}
