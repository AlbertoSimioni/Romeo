#include "protocolspanel.h"
#include "ui_protocolspanel.h"
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QDragLeaveEvent>
#include <QDragMoveEvent>
#include <QMimeData>
using namespace romeo::view::mainWindow;
using namespace romeo::model::datasets;
ProtocolsPanel::ProtocolsPanel(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ProtocolsPanel)
{
    ui->setupUi(this);
    setAcceptDrops(true);
}

ProtocolsPanel::~ProtocolsPanel()
{
    delete ui;
}


void ProtocolsPanel::connectUI(){
    //connect(currentDataset,SIGNAL())
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
        QList<QListWidgetItem*> match = ui->protocolsList->findItems(protocol,Qt::MatchExactly);
        if(match.isEmpty()){
            ui->protocolsList->addItem(protocol);
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
    currentDataset = dataset;
}
