
/**
* \file abouthelpcontroller.cpp
* \author Matteo Pozza
* \date 2014-02-17
**
* \brief Header della classe AboutHelpController del package romeo::controller
*/

#include "abouthelpcontroller.h"

using namespace romeo::controller;
using namespace romeo::view::dialogs;


AboutHelpController* AboutHelpController::instance=0;


AboutHelpController::AboutHelpController(view::mainWindow::MainWindow* mainw, QObject *parent) :
    mainWindow(mainw), helpDialog(0), aboutDialog(0),QObject(parent)
{

    connectViewsSignals();
}

AboutHelpController* AboutHelpController::getInstance(view::mainWindow::MainWindow* mainw, QObject *parent){
    if(instance == 0){
        instance = new AboutHelpController(mainw,parent);
    }
    return instance;
}

void AboutHelpController::connectViewsSignals(){
    connect(mainWindow, SIGNAL(openHelpDialog()), this,SLOT(viewHelpDialog()));
    connect(mainWindow,SIGNAL(openAboutDialog()),this,SLOT(viewAboutDialog()));
}

void AboutHelpController::viewHelpDialog()
{
    if(helpDialog == 0){
        helpDialog=new HelpDialog(mainWindow);
    }
    helpDialog->exec();
}

void AboutHelpController::viewAboutDialog()
{
    if(aboutDialog == 0){
        aboutDialog=new AboutDialog(mainWindow);
    }
    aboutDialog->exec();
}
