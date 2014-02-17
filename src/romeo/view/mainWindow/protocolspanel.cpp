#include "protocolspanel.h"
#include "ui_protocolspanel.h"
using namespace romeo::view::mainWindow;
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
