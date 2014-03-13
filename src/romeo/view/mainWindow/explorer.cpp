/**
* \file explorer.cpp
* \author Alessandro Strenghetto
* \date 2014-02-17
**
* \brief Header della classe Explorer del package romeo::view::mainWindow
*/

#include "explorer.h"
#include "ui_explorer.h"
using namespace romeo::view::mainWindow;
Explorer::Explorer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Explorer)
{
    ui->setupUi(this);
    ui->splitter->setStretchFactor(0,1);
    ui->splitter->setStretchFactor(1,1);
}

Explorer::~Explorer()
{
    delete ui;
}


DatasetsExplorer* Explorer::getDatasetsExplorer(){
    return ui->datasetsExplorer;
}

ProtocolsExplorer* Explorer::getProtocolsExplorer(){
    return ui->protocolsExplorer;
}
