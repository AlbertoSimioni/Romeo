#include "testcontroller.h"
#include "ui_newdatasetdialog.h"
#include "ui_addsubjectdialog.h"

TestDatasetsController::TestDatasetsController(QObject *parent) :
    QObject(parent){
}


void TestDatasetsController::getInstance(){
    QCOMPARE(DatasetsController::getInstance(),DatasetsController::getInstance());
}



void TestDatasetsController::checkDatasetName(){

    DatasetsController *datasetscontroller = DatasetsController::getInstance();

    datasetscontroller->checkDatasetName(QString("notExists"));
    QCOMPARE(datasetscontroller->newDatasetDialog->ui->ErrorLabel->isHidden(),true);

    DatasetsList *list = DatasetsList::getInstance();

    QString datasetName = "dataset2D";
    list->addDataset(datasetName,romeo::model::TYPE2D);

    datasetscontroller->checkDatasetName(datasetName);
    QCOMPARE(datasetscontroller->newDatasetDialog->ui->okCancel->button(QDialogButtonBox::Ok)->isEnabled(),false);
}

void TestDatasetsController::checkSubjectName(){

    QDir dataTest = QDir::current();
    dataTest.cd("..");
    dataTest.cd("..");
    dataTest.cd("tests");

    DatasetsController *datasetscontroller = DatasetsController::getInstance();

    DatasetsList *list = DatasetsList::getInstance();

    QString datasetName = "mydataset2D";
    list->addDataset(datasetName,romeo::model::TYPE2D);

    AbstractDataset *ad= list->getDataset(datasetName);
    QString subjName = "subjName3";
    QString subjFileSubject = dataTest.absolutePath().append("/images/image.tif");
    QString subjMask = dataTest.absolutePath().append("/images/mask.tif");

    datasetscontroller->mainWindow->getDatasetPanel()->setCurrentDataset(ad);

    datasetscontroller->mainWindow->getDatasetPanel()->getCurrentDataset()->createNewSubject(subjName,subjFileSubject,subjMask);

    datasetscontroller->checkSubjectName(subjName);

    QCOMPARE(datasetscontroller->addSubjectDialog->ui->okCancel->button(QDialogButtonBox::Ok)->isEnabled(),false);

    datasetscontroller->mainWindow->getDatasetPanel()->getCurrentDataset()->deleteSubject(subjName);

    datasetscontroller->checkSubjectName(subjName);

    QCOMPARE(datasetscontroller->addSubjectDialog->ui->okCancel->button(QDialogButtonBox::Ok)->isEnabled(),true);
}

void TestDatasetsController::addDataset(){

    DatasetsController *datasetscontroller = DatasetsController::getInstance();

    DatasetsList *list = DatasetsList::getInstance();

    QString datasetName = "myDataset2D";
    datasetscontroller->addDataset(datasetName,romeo::model::TYPE2D);

    QCOMPARE(list->getDataset(datasetName)->getName(),datasetName);
}

void TestDatasetsController::addSubject(){
    QDir dataTest = QDir::current();
    dataTest.cd("..");
    dataTest.cd("..");
    dataTest.cd("tests");

    DatasetsController *datasetscontroller = DatasetsController::getInstance();

    DatasetsList *list = DatasetsList::getInstance();

    QString datasetName = "newDataset";
    list->addDataset(datasetName,romeo::model::TYPE2D);

    AbstractDataset *ad = list->getDataset(datasetName);
    QString subjName = "subjName";
    QString subjFileSubject = dataTest.absolutePath().append("/images/image.tif");
    QString subjMask = dataTest.absolutePath().append("/images/mask.tif");

    datasetscontroller->mainWindow->getDatasetPanel()->setCurrentDataset(ad);

    datasetscontroller->addSubject(subjName,subjFileSubject,subjMask);

    QCOMPARE(list->getDataset(datasetName)->getSubject(subjName)->getName(),subjName);
}

void TestDatasetsController::deleteSubject(){

    QDir dataTest = QDir::current();
    dataTest.cd("..");
    dataTest.cd("..");
    dataTest.cd("tests");

    DatasetsController *datasetscontroller = DatasetsController::getInstance();

    DatasetsList *list = DatasetsList::getInstance();

    QString datasetName = "newDataset2";
    list->addDataset(datasetName,romeo::model::TYPE2D);

    Dataset2D *ds2d = dynamic_cast<Dataset2D*>(list->getDataset(datasetName));
    QString subjName = "subjName2";
    QString subjFileSubject = dataTest.absolutePath().append("/images/image.tif");
    QString subjMask = dataTest.absolutePath().append("/images/mask.tif");

    datasetscontroller->mainWindow->getDatasetPanel()->setCurrentDataset(ds2d);

    datasetscontroller->mainWindow->getDatasetPanel()->getCurrentDataset()->createNewSubject(subjName,subjFileSubject,subjMask);

    QCOMPARE(list->getDataset(datasetName)->subjects.isEmpty(),false);

    datasetscontroller->deleteSubject(subjName);

    QCOMPARE(list->getDataset(datasetName)->subjects.isEmpty(),true);
}

void TestDatasetsController::deleteCurrentDataset(){

    DatasetsController *datasetscontroller = DatasetsController::getInstance();

    DatasetsList *dl = DatasetsList::getInstance();

    QString nameD1 = "Dataset1";
    QString nameD2 = "Dataset2";

    Dataset2D *ds2d = new Dataset2D(nameD1);

    dl->addDataset(nameD1,romeo::model::TYPE2D);
    dl->addDataset(nameD2,romeo::model::TYPE2D);

    datasetscontroller->mainWindow->getDatasetPanel()->setCurrentDataset(ds2d);

    datasetscontroller->deleteCurrentDataset();

    QVERIFY(datasetscontroller->mainWindow->getDatasetPanel()->getCurrentDataset()->getName() != nameD1);

    delete ds2d;
}

void TestDatasetsController::getMainWindow(){

    DatasetsController *datasetscontroller = DatasetsController::getInstance();

    QCOMPARE(datasetscontroller->getMainWindow(),datasetscontroller->mainWindow);
}
