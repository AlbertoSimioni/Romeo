#include "testmainwindow.h"
#include "ui_mainwindow.h"

TestMainWindow::TestMainWindow(QObject *parent) :
    QObject(parent){
}



void TestMainWindow::getDatasetsExplorer(){
    MainWindow *mw = new MainWindow();

    QCOMPARE(mw->getDatasetsExplorer(),mw->ui->explorer->getDatasetsExplorer());

    delete mw;
}

void TestMainWindow::getProtocolsExplorer(){
    MainWindow *mw = new MainWindow();

    QCOMPARE(mw->getProtocolsExplorer(),mw->ui->explorer->getProtocolsExplorer());

    delete mw;
}

void TestMainWindow::getDatasetPanel(){
    MainWindow *mw = new MainWindow();

    QCOMPARE(mw->getDatasetPanel(),mw->ui->datasetPanel);

    delete mw;
}

void TestMainWindow::onDeleteProtocolClicked(){
    MainWindow *mw = new MainWindow();
    QSignalSpy spy(mw,SIGNAL(deleteProtocol(QString)));

    mw->onDeleteProtocolClicked();

    QCOMPARE(spy.count(),0);

    delete mw;
}

void TestMainWindow::getFileSystemExplorer(){
    MainWindow *mw = new MainWindow();

    QCOMPARE(mw->getFileSystemExplorer(),mw->ui->fileSystemExplorer);

    delete mw;
}
