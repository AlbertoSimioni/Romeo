#include "viewmanager.h"
#include <src/romeo/view/dialogs/newdatasetdialog.h>
using namespace romeo::view;
using namespace romeo::view::dialogs;
using namespace romeo::view::mainWindow;


ViewManager* ViewManager::instance = 0;


ViewManager::ViewManager(QObject *parent): QObject(parent)
{
    mainWindow = new MainWindow();//controllare per il parent
    newDatasetDialog = new NewDatasetDialog(mainWindow);
    protocolDialog = new ProtocolDialog(mainWindow);
   executeDialog = new ExecuteDialog(mainWindow);
   newAlgorithmDialog = new NewAlgorithmDialog(mainWindow);
   newFeatureDialog = new NewFeatureDialog(mainWindow);
   addSubjectDialog = new AddSubjectDialog (mainWindow);

   mainWindow->show();
}

ViewManager::~ViewManager()
{   //è necessario chiamare il distruttore solo della mainWindow perchè tutti gli altri dialoghi sono suoi discendenti
    delete mainWindow;
}

ViewManager* ViewManager::getInstance(QObject *parent){
    if(instance == 0){
        instance = new ViewManager(parent);
    }
    return instance;
}

MainWindow *ViewManager::getMainWindow() const
{
    return mainWindow;
}


NewDatasetDialog *ViewManager::getNewDatasetDialog() const
{
    return newDatasetDialog;
}

dialogs::ProtocolDialog *ViewManager::getProtocolDialog() const
{
    return protocolDialog;
}


dialogs::NewFeatureDialog *ViewManager::getNewFeatureDialog() const
{
    return newFeatureDialog;
}



dialogs::NewAlgorithmDialog *ViewManager::getNewAlgorithmDialog() const
{
    return newAlgorithmDialog;
}

dialogs::AddSubjectDialog *ViewManager::getAddSubjectDialog() const
{
    return addSubjectDialog;
}


dialogs::ExecuteDialog *ViewManager::getExecuteDialog() const
{
    return executeDialog;
}



void ViewManager::showNewDataset(){
    newDatasetDialog->exec();
}


void ViewManager::showNewProtocol(){
    protocolDialog->exec();
}
