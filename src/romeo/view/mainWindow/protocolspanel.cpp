
#include "protocolspanel.h"
#include "ui_protocolspanel.h"

ProtocolsPanel::ProtocolsPanel(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ProtocolsPanel)
{
    ui->setupUi(this);
}

ProtocolsPanel::~ProtocolsPanel()
{
    delete ui;
}
