/**
* \file protocolspanel.cpp
* \author Alessandro Strenghetto
* \date 2014-02-17
**
* \brief Header della classe ProtocolsPanel del package romeo::view::mainWindow
*/

#include "protocolspanel.h"
#include "ui_protocolspanel.h"
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QDragLeaveEvent>
#include <QDragMoveEvent>
#include <QMimeData>
#include <QDebug>
#include <QDesktopServices>
#include <QSettings>

using namespace romeo::view::mainWindow;
using namespace romeo::model::datasets;
using namespace romeo::model::protocols;
ProtocolsPanel::ProtocolsPanel(QWidget *parent) :
    QWidget(parent), currentDataset(0),
    ui(new Ui::ProtocolsPanel)
{
    ui->setupUi(this);
    setAcceptDrops(true);
    connectUI();
}

ProtocolsPanel::~ProtocolsPanel()
{
    delete ui;
}


void ProtocolsPanel::connectUI(){
    connect(ui->protocolsList,SIGNAL(currentItemChanged(QTreeWidgetItem*,QTreeWidgetItem*)),this,SLOT(changeDescription()));
    connect(ui->protocolsList,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(openResultFolder()));
    connect(ui->newButton,SIGNAL(clicked()),this,SIGNAL(openAssociateProtocolDialog()));
    connect(ui->deleteButton,SIGNAL(clicked()),this,SLOT(onDeleteClicked()));
}

void ProtocolsPanel::dragEnterEvent(QDragEnterEvent * event){
    event->accept();
}

void ProtocolsPanel::dragLeaveEvent(QDragLeaveEvent * event){
    event->accept();

}
void ProtocolsPanel::dragMoveEvent(QDragMoveEvent * event){
     event->accept();

}
void ProtocolsPanel::dropEvent(QDropEvent * event){

    if (event->mimeData()->hasFormat("protocol")) {
        event->accept();
        event->setDropAction(Qt::MoveAction);
        QString protocol = event->mimeData()->data("protocol");
        QList<QTreeWidgetItem*> match = ui->protocolsList->findItems(protocol,Qt::MatchExactly);
        if(match.isEmpty()){
            QString protocolName = protocol.split("  [Test").takeFirst();
            QSettings settings;
            settings.setValue("selectedProtocol",protocolName);
            emit associateProtocol(protocolName);
        }
    } else
        event->ignore();

}

AbstractDataset *ProtocolsPanel::getCurrentDataset() const
{
    return currentDataset;
}

void ProtocolsPanel::setCurrentDataset(romeo::model::datasets::AbstractDataset *dataset)
{
    if(currentDataset != 0){
        disconnect(currentDataset,SIGNAL(protocolsModified()),this,SLOT(fillProtocolsList()));
        disconnect(currentDataset,SIGNAL(newResults()),this,SLOT(fillProtocolsList()));
    }
    currentDataset = dataset;

    if(currentDataset != 0){
        connect(currentDataset,SIGNAL(protocolsModified()),this,SLOT(fillProtocolsList()));
        connect(currentDataset,SIGNAL(newResults()),this,SLOT(fillProtocolsList()));
    }
    fillProtocolsList();
}


void ProtocolsPanel::fillProtocolsList(){
    ui->protocolsList->clear();
    ui->descriptionText->clear();

    if(currentDataset != 0){

        ui->newButton->setEnabled(true);
        ui->deleteButton->setEnabled(true);
        setAcceptDrops(true);
        QList<AbstractProtocol*> protocols = currentDataset->getAssociatedProtocolsList();
        for(int i = 0; i< protocols.size(); i++){

            AbstractProtocol* protocol = protocols[i];
            QString protocolName = protocol->getName();

            QStringList protocolResults = currentDataset->getProtocolResults(protocolName);

            if(protocol->getTest()) protocolName = protocolName.append("  [Test]");
            addProtocol(protocolName,protocolResults);

        }

    }

    else{

        setAcceptDrops(false);
        ui->newButton->setEnabled(false);
        ui->deleteButton->setEnabled(false);
    }

}


void ProtocolsPanel::addProtocol(QString protocolName, QStringList results){
    QTreeWidgetItem *protocolItem =new QTreeWidgetItem(ui->protocolsList);
    protocolItem->setText(0,protocolName);
    QSettings settings;
    QString selectedProtocol = settings.value("selectedProtocol").toString();
    if(selectedProtocol == protocolName.split("  [Test").takeFirst())
        ui->protocolsList->setCurrentItem( protocolItem);
    for(int i = 0; i < results.size(); i++){
         QTreeWidgetItem *resultItem =new QTreeWidgetItem();
         resultItem->setText(0,results[i]);
         protocolItem->addChild(resultItem);
    }
}


void ProtocolsPanel::changeDescription(){
    QTreeWidgetItem* currentItem = ui->protocolsList->currentItem();
    if(currentItem){
        QTreeWidgetItem* parent = currentItem->parent();
        if(!parent){
            QString protocolName = currentItem->data(0,Qt::DisplayRole).toString().split("  [Test").takeFirst();
            QSettings settings;
            settings.setValue("selectedProtocol",protocolName);
            AbstractProtocol * protocol = currentDataset->getProtocol(protocolName);
            QString textDescription=protocol->getDescription();
            if(!textDescription.isEmpty())
                textDescription+="\n\n";
            textDescription+="Algorithm: \t" + protocol->getAlgorithmName() +"\n\n";
            QStringList features=protocol->getFeaturesName();

            for (int i=0; i<features.length(); ++i){
                if(i==0)
                    textDescription+="Features: \t";
                textDescription+=features.at(i) + "\n\t";
            }
            ui->descriptionText->setText(textDescription);
         }
    }
    else ui->descriptionText->clear();
}

void ProtocolsPanel::openResultFolder(){
    QTreeWidgetItem* currentItem = ui->protocolsList->currentItem();
    QTreeWidgetItem* parent = currentItem->parent();
    if(parent){
        QString protocolName = parent->data(0,Qt::DisplayRole).toString().split("  [Test").takeFirst();
        QString pathResult = currentDataset->getResultPath(protocolName,currentItem->data(0,Qt::DisplayRole).toString());
        QDesktopServices::openUrl(QUrl(pathResult));
    }
}


void ProtocolsPanel::onDeleteClicked(){
    QTreeWidgetItem* currentItem = ui->protocolsList->currentItem();
    if(currentItem){
        QTreeWidgetItem* parent = currentItem->parent();
        if(!parent){
         QString protocolName = currentItem->data(0,Qt::DisplayRole).toString().split("  [Test").takeFirst();
            emit removeProtocolAssociation(protocolName);
        }
    }
}

QString ProtocolsPanel::getSelectedProtocol(){
    QString protocolName;
    QTreeWidgetItem* currentItem = ui->protocolsList->currentItem();
    if(currentItem){
        QTreeWidgetItem* parent = currentItem->parent();
        if(!parent){
            protocolName = currentItem->data(0,Qt::DisplayRole).toString().split("  [Test").takeFirst();

         }
    }
    return protocolName;
}
