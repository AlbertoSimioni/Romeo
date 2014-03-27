#include "testexecutepanel.h"
#include "ui_executepanel.h"

TestExecutePanel::TestExecutePanel(QObject *parent) :
    QObject(parent){
}

void TestExecutePanel::setCurrentDataset(){
    ExecutePanel *ep = new ExecutePanel();
    QString datasetName ="Dataset2D";
    Dataset2D *dat2d = new Dataset2D(datasetName);
    ep->setCurrentDataset(dat2d);
    QCOMPARE(ep->currentDataset,dat2d);

    datasetName = "Dataset2DT";
    Dataset2DT *dat2dt = new Dataset2DT(datasetName);
    ep->setCurrentDataset(dat2dt);
    QCOMPARE(ep->currentDataset,dat2dt);

    datasetName = "Dataset3D";
    Dataset3D *dat3d = new Dataset3D(datasetName);
    ep->setCurrentDataset(dat3d);
    QCOMPARE(ep->currentDataset,dat3d);

    datasetName = "Dataset3DT";
    Dataset3DT *dat3dt = new Dataset3DT(datasetName);
    ep->setCurrentDataset(dat3dt);
    QCOMPARE(ep->currentDataset,dat3dt);

    delete dat2d;
    delete ep;
}

void TestExecutePanel::onStartClicked(){
    ExecutePanel *ep = new ExecutePanel();
    QSignalSpy spy(ep,SIGNAL(executeAnalysis(QString,bool,bool,bool,QString)));

    ep->onStartClicked();
    QCOMPARE(spy.count(),1);

    delete ep;
}

void TestExecutePanel::onViewResultsClicked(){
    ExecutePanel *ep = new ExecutePanel();

    ep->ui->viewResultsCheck->setChecked(true);
    ep->ui->saveFeaturesCheck->setChecked(true);
    ep->onViewResultsCliked(true);
    QCOMPARE(ep->ui->viewFeaturesCheck->isEnabled(),true);

    ep->ui->viewResultsCheck->setChecked(true);
    ep->ui->saveFeaturesCheck->setChecked(true);
    ep->onViewResultsCliked(false);
    QCOMPARE(ep->ui->viewFeaturesCheck->isEnabled(),true);

    ep->ui->viewResultsCheck->setChecked(false);
    ep->ui->saveFeaturesCheck->setChecked(false);
    ep->onViewResultsCliked(true);
    QCOMPARE(ep->ui->viewFeaturesCheck->isEnabled(),false);

    ep->ui->viewResultsCheck->setChecked(false);
    ep->ui->saveFeaturesCheck->setChecked(false);
    ep->onViewResultsCliked(false);
    QCOMPARE(ep->ui->viewFeaturesCheck->isEnabled(),false);

    delete ep;
}
