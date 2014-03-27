#ifndef TESTMAINWINDOW_H
#define TESTMAINWINDOW_H

#include <QtTest>
#define private public
#include <../src/romeo/view/mainWindow/mainwindow.h>


using namespace romeo::view::mainWindow;

class TestMainWindow : public QObject
{
    Q_OBJECT

public:
    explicit TestMainWindow(QObject *parent = 0);

private slots:
    void getDatasetsExplorer();
    void getProtocolsExplorer();
    void getDatasetPanel();
    void onDeleteProtocolClicked();
    void getFileSystemExplorer();
};


#endif // TESTMAINWINDOW_H
