#include "protocolsexplorer.h"
#include "ui_protocolsexplorer.h"
using namespace romeo::view::mainWindow;
using namespace romeo::model::protocols;
ProtocolsExplorer::ProtocolsExplorer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ProtocolsExplorer)
{
    ui->setupUi(this);
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
}

