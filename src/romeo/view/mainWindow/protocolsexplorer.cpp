#include "protocolsexplorer.h"
#include "ui_protocolsexplorer.h"
using namespace romeo::view::mainWindow;
using namespace romeo::model::protocols;
ProtocolsExplorer::ProtocolsExplorer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ProtocolsExplorer)
{
    ui->setupUi(this);
    ui->protocolsTable->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->protocolsTable->setDragEnabled(true);
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

            ui->protocolsTable->addItem(name);

        }
    }
}
