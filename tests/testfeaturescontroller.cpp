#include "testfeaturescontroller.h"
#include "ui_newfeaturedialog.h"

TestFeaturesController::TestFeaturesController(QObject *parent) :
    QObject(parent){
}


void TestFeaturesController::getInstance(){
    QCOMPARE(FeaturesController::getInstance(),FeaturesController::getInstance());
}


void TestFeaturesController::checkFeatureName(){
    FeaturesController *featurescontroller = FeaturesController::getInstance();

    featurescontroller->checkFeatureName(QString("notExists"));
    QCOMPARE(featurescontroller->newFeatureDialog->ui->errorLabel->isHidden(),true);

    features::FeaturesList *list = features::FeaturesList::getInstance();

    QString featName = "featName";
    features::FirstOrderFeature *foFeat = new features::FirstOrderFeature(featName,QString("fodylp"),QString("fodyfn"),QString("fodescription"));

    list->addFeature(foFeat);

    featurescontroller->checkFeatureName(featName);
    QCOMPARE(featurescontroller->newFeatureDialog->ui->okCancel->button(QDialogButtonBox::Ok)->isEnabled(),false);

    delete foFeat;
}


void TestFeaturesController::addFeature(){

    FeaturesController *featurescontroller = FeaturesController::getInstance();

    features::FeaturesList *list = features::FeaturesList::getInstance();

    QString featName = "featName3";

    featurescontroller->addFeature(featName,QString("fodescription"),QString("fodyfn"),QString("fodylp"),features::FIRSTORDER);

    QCOMPARE(list->getFeature(featName)->getName(),featName);
}

