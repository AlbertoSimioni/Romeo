#include "mainwindow.h"
#include "ui_mainwindow.h"
using namespace romeo::view::mainWindow;
using namespace romeo::model::protocols;
using namespace romeo::model::datasets;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->sidebarFrame->setTabText(0, "Explorer");
    ui->sidebarFrame->setTabText(1, "File System");
    connectActionsToSignal();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::connectActionsToSignal(){
    connect(ui->actionNew_Dataset,SIGNAL(triggered()),this,SIGNAL(openNewDatasetDialog()));
    connect(ui->actionNewProtocol,SIGNAL(triggered()),this,SIGNAL(openNewPortocolDialog()));
    connect(ui->actionAdd_Algorithm,SIGNAL(triggered()),this,SIGNAL(openNewAlgorithmDialog()));
    connect(ui->actionAdd_Feature,SIGNAL(triggered()),this,SIGNAL(openNewFeatureDialog()));
    connect(ui->actionAlgorithms_List,SIGNAL(triggered()),this,SIGNAL(openAlgorithmsListDialog()));
    connect(ui->actionFeatures_List,SIGNAL(triggered()),this,SIGNAL(openFeaturesListDialog()));
    connect(ui->actionRemoveDataset,SIGNAL(triggered()),this,SIGNAL(deleteCurrentDataset()));
    connect(ui->actionProtocolRemove,SIGNAL(triggered()),this,SLOT(onDeleteProtocolClicked()));
}


DatasetsExplorer* MainWindow::getDatasetsExplorer(){
    return ui->explorer->getDatasetsExplorer();
}

ProtocolsExplorer* MainWindow::getProtocolsExplorer(){
    return ui->explorer->getProtocolsExplorer();
}

DatasetPanel* MainWindow::getDatasetPanel(){
    return ui->datasetPanel;
}


void MainWindow::onDeleteProtocolClicked(){
    QString selectedProtocolName = ui->explorer->getProtocolsExplorer()->getSelectedProtocolName();
    if(!selectedProtocolName.isEmpty())
        emit deleteProtocol(selectedProtocolName);
}


FileSystemExplorer* MainWindow::getFileSystemExplorer(){
    return ui->fileSystemExplorer;
}
