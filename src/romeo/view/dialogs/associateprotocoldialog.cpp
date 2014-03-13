/**
* \file associateprotocoldialog.cpp
* \author Alessandro Strenghetto
* \date 2014-02-17
**
* \brief Header della classe AssociateProtocolDialog del package romeo::view::dialogs
*/

#include "associateprotocoldialog.h"
#include "ui_associateprotocoldialog.h"
using namespace romeo::view::dialogs;
using namespace romeo::model::protocols;
AssociateProtocolDialog::AssociateProtocolDialog(ProtocolsList *pl, QWidget *parent) :
    QDialog(parent), protocolsList(pl), currentProtocolsType(STATIC),
    ui(new Ui::AssociateProtocolDialog)
{
    ui->setupUi(this);
    connectUI();
    fillProtocolsList();
}

AssociateProtocolDialog::~AssociateProtocolDialog()
{
    delete ui;
}

void AssociateProtocolDialog::connectUI(){
    connect(ui->cancelButton,SIGNAL(clicked()),this,SLOT(reject()));
    connect(protocolsList,SIGNAL(protocolsListModified()),this,SLOT(fillProtocolsList()));
    connect(ui->associateButton,SIGNAL(clicked()),this,SLOT(onAssociateClicked()));
}

void AssociateProtocolDialog::setCurrentProtocolsType(const ProtocolType &value)
{
    currentProtocolsType = value;
    fillProtocolsList();
}


void AssociateProtocolDialog::fillProtocolsList(){
    ui->protocolsList->clear();
    QList<AbstractProtocol*> protocols = protocolsList->getProtocolsList();

    for(int i = 0; i< protocols.size(); i++){
        QString name = protocols[i]->getName();
        if(protocols[i]->getTest()){
           name.append("  [Test]");
        }
        if(protocols[i]->getType() == currentProtocolsType)
            ui->protocolsList->addItem(name);
    }
}


void AssociateProtocolDialog::onAssociateClicked(){

    QListWidgetItem* currentProtocol = ui->protocolsList->currentItem();
    if(currentProtocol){
        QString protocolName = currentProtocol->text().split("  [Test").takeFirst();
        emit associateProtocol(protocolName);
        accept();
    }

}
