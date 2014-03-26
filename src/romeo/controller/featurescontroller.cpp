/**
* \file featurescontroller.cpp
* \author Matteo Pozza
* \date 2014-02-17
**
* \brief Header della classe FeaturesController del package romeo::controller
*/
#include "featurescontroller.h"
using namespace romeo::controller;
using namespace romeo::model::protocols::features;
using namespace romeo::view::dialogs;


FeaturesController* FeaturesController::instance=0;
FeaturesController::FeaturesController(view::mainWindow::MainWindow* mainw,QObject *parent) :
    mainWindow(mainw),QObject(parent)
{
    featuresList = FeaturesList::getInstance();
    featuresListDialog = new FeaturesListDialog(featuresList,mainWindow);

    newFeatureDialog = new NewFeatureDialog(mainWindow);
    connectViewsSignals();
}


FeaturesController* FeaturesController::getInstance(view::mainWindow::MainWindow* mainw,QObject *parent){
    if(instance == 0){
        instance = new FeaturesController(mainw,parent);
    }

    return instance;
}

void FeaturesController::connectViewsSignals(){
    connect(newFeatureDialog,SIGNAL(nameChanged(QString)),this,SLOT(checkFeatureName(QString)));
    connect(newFeatureDialog,SIGNAL(createFeature(QString,QString,QString,QString,romeo::model::protocols::features::FeatureType)),this,SLOT(addFeature(QString,QString,QString,QString,romeo::model::protocols::features::FeatureType)));
    connect(mainWindow,SIGNAL(openFeaturesListDialog()),this,SLOT(viewFeaturesListDialog()));
    connect(mainWindow,SIGNAL(openNewFeatureDialog()),this,SLOT(viewNewFeatureDialog()));

}


void FeaturesController::viewNewFeatureDialog(){
    newFeatureDialog->exec();
}


void FeaturesController::viewFeaturesListDialog(){
    featuresListDialog->exec();
}



void FeaturesController::checkFeatureName(QString featureName){
    if(featuresList->getFeature(featureName)){
            newFeatureDialog->showErrorName(true);
    }
    else{
        newFeatureDialog->showErrorName(false);
    }
}

void FeaturesController::addFeature(QString name, QString desc, QString dyfn, QString dylp, FeatureType type){
    featuresList->addFeature(name,type,desc,dylp,dyfn);
}
