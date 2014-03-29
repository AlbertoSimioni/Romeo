#include "testsubjectspanel.h"
#include "ui_subjectspanel.h"

TestSubjectsPanel::TestSubjectsPanel(QObject *parent) :
    QObject(parent){
}

void TestSubjectsPanel::setCurrentDataset(){
    SubjectsPanel *sp = new SubjectsPanel();
    QString datasetName ="Dataset2D";
    Dataset2D *dat2d = new Dataset2D(datasetName);
    sp->setCurrentDataset(dat2d);
    QCOMPARE(sp->currentDataset,dat2d);

    datasetName = "Dataset2DT";
    Dataset2DT *dat2dt = new Dataset2DT(datasetName);
    sp->setCurrentDataset(dat2dt);
    QCOMPARE(sp->currentDataset,dat2dt);

    datasetName = "Dataset3D";
    Dataset3D *dat3d = new Dataset3D(datasetName);
    sp->setCurrentDataset(dat3d);
    QCOMPARE(sp->currentDataset,dat3d);

    datasetName = "Dataset3DT";
    Dataset3DT *dat3dt = new Dataset3DT(datasetName);
    sp->setCurrentDataset(dat3dt);
    QCOMPARE(sp->currentDataset,dat3dt);

    delete dat2d;
    delete dat2dt;
    delete dat3d;
    delete dat3dt;
    delete sp;
}

void TestSubjectsPanel::getCurrentDataset(){
    SubjectsPanel *sp = new SubjectsPanel();
    QString datasetName ="Dataset2D";
    Dataset2D *dat2d = new Dataset2D(datasetName);
    sp->currentDataset = dat2d;
    QCOMPARE(sp->getCurrentDataset(),dat2d);

    datasetName = "Dataset2DT";
    Dataset2DT *dat2dt = new Dataset2DT(datasetName);
    sp->currentDataset = dat2dt;
    QCOMPARE(sp->getCurrentDataset(),dat2dt);

    datasetName = "Dataset3D";
    Dataset3D *dat3d = new Dataset3D(datasetName);
    sp->currentDataset = dat3d;
    QCOMPARE(sp->getCurrentDataset(),dat3d);

    datasetName = "Dataset3DT";
    Dataset3DT *dat3dt = new Dataset3DT(datasetName);
    sp->currentDataset = dat3dt;
    QCOMPARE(sp->getCurrentDataset(),dat3dt);

    delete dat2d;
    delete dat2dt;
    delete dat3d;
    delete dat3dt;
    delete sp;
}

void TestSubjectsPanel::fillSubjectsList(){
    SubjectsPanel *sp = new SubjectsPanel();

    sp->fillSubjectsList();
    QCOMPARE(sp->ui->deleteButton->isEnabled(),false);

    delete sp;
}

void TestSubjectsPanel::onDeleteClicked(){
    SubjectsPanel *sp = new SubjectsPanel();
    QSignalSpy spy(sp,SIGNAL(subjectsAnalysis(QString,bool,bool,bool,QString)));

    sp->onDeleteClicked();
    QCOMPARE(spy.count(),0);

    delete sp;
}

void TestSubjectsPanel::getCheckedSubjects(){
    SubjectsPanel *sp = new SubjectsPanel();

    QCOMPARE(sp->getCheckedSubjects().isEmpty(),true);

    delete sp;
}
