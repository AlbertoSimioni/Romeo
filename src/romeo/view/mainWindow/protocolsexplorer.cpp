/**
* \file protocolsexplorer.cpp
* \author Alessandro Strenghetto
* \date 2014-02-17
**
* \brief Header della classe ProtocolsExplorer del package romeo::view::mainWindow
*/

#include "protocolsexplorer.h"
#include "ui_protocolsexplorer.h"

using namespace romeo::view::mainWindow;
using namespace romeo::model::protocols;

ProtocolsExplorer::ProtocolsExplorer(QWidget *parent) :
    QWidget(parent),currentProtocolsType(STATIC),protocolsList(0),
    ui(new Ui::ProtocolsExplorer)
{
    ui->setupUi(this);
    ui->protocolsTable->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->protocolsTable->setDragEnabled(true);
    connect(ui->protocolsTable,SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)),this,SLOT(onItemDoubleClicked()));
}

ProtocolsExplorer::~ProtocolsExplorer()
{
    delete ui;
}
ProtocolsList *ProtocolsExplorer::getProtocolsList() const
{
    return protocolsList;

}

void ProtocolsExplorer::setProtocolsList(ProtocolsList *value)
{
    protocolsList = value;
    connect(protocolsList,SIGNAL(protocolsListModified()),this,SLOT(fillProtocolsExplorer()));
    fillProtocolsExplorer();
}


void ProtocolsExplorer::fillProtocolsExplorer(){
    ui->protocolsTable->clear();
    if(protocolsList){
        QList<AbstractProtocol*> protocols = protocolsList->getProtocolsList();

        for(int i = 0; i< protocols.size(); i++){
            QString name = protocols[i]->getName();
            if(protocols[i]->getTest()){
               name.append("  [Test]");
            }
            if(protocols[i]->getType() == currentProtocolsType){
                QTreeWidgetItem *itm =new QTreeWidgetItem(ui->protocolsTable);
                itm->setText(0,name);
            }

        }
    }
}

void ProtocolsExplorer::setCurrentProtocolsType(const romeo::model::protocols::ProtocolType &value)
{
    currentProtocolsType = value;
    fillProtocolsExplorer();
}



QString ProtocolsExplorer::getSelectedProtocolName(){
    QList<QTreeWidgetItem*> selectedProtocol = ui->protocolsTable->selectedItems();
    QString protocolName = QString();
    if(!selectedProtocol.isEmpty()){
        protocolName = selectedProtocol.at(0)->data(0,Qt::EditRole).toString().split("  [Test").takeFirst();
    }
    return protocolName;
}


void ProtocolsExplorer::onItemDoubleClicked(){
    QString name = getSelectedProtocolName();
    emit openProtocol(name);
}
