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

   mainWindow->show();
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


void ViewManager::showNewDataset(){
    newDatasetDialog->exec();
}
