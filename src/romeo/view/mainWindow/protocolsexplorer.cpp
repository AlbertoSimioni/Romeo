#include "protocolsexplorer.h"
#include "ui_protocolsexplorer.h"
using namespace romeo::view::mainWindow;
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
