#include "testexecutedialog.h"
#include "ui_executedialog.h"
#include <QPushButton>

TestExecuteDialog::TestExecuteDialog(QObject *parent) :
    QObject(parent)
{
}

void TestExecuteDialog::showImage(){
    ExecuteDialog *exDialogTest1=new ExecuteDialog(0);
    QString datasetName="DatasetProva";
    AbstractDataset *dat2d=new Dataset2D(datasetName);
    exDialogTest1->prepareAnalysis(dat2d,false,false,2,1,2);
    QDir image = QDir::current();
    image.cd("..");
    image.cd("..");
    image.cd("tests");
    image.cd("images");
    exDialogTest1->showImage(image.absolutePath().append("/image.png"));
    QCOMPARE(exDialogTest1->ui->widget->isHidden(),false);
    delete exDialogTest1;

    ExecuteDialog *exDialogTest2=new ExecuteDialog(0);
    QString datasetName2="DatasetProva";
    AbstractDataset *dat3d=new Dataset3D(datasetName2);
    exDialogTest2->prepareAnalysis(dat3d,false,false,2,1,2);
    exDialogTest2->showImage(image.absolutePath().append("/image3d_K-means.nii"));
    QCOMPARE(exDialogTest2->ui->widget->isHidden(),false);
    delete dat2d;
    delete dat3d;
    delete exDialogTest2;
}

void TestExecuteDialog::analysisFinished(){
    ExecuteDialog *exec=new ExecuteDialog();

    exec->analysisFinished();
    QCOMPARE(exec->ui->currentLabel->text(),QString("Aborted"));
    exec->ui->progressBar->setValue((exec->nImagesPerSubject)*(exec->nSubjects));
    exec->analysisFinished();
    QCOMPARE(exec->ui->currentLabel->text(),QString("Completed"));
}

void TestExecuteDialog::onNextClicked(){
    ExecuteDialog *exec=new ExecuteDialog(0);
    QString datasetName="DatasetProva";
    Dataset2D *dat2d=new Dataset2D(datasetName);
    exec->prepareAnalysis(dat2d,false,true,2,1,2);
    QDir image = QDir::current();
    image.cd("..");
    image.cd("..");
    image.cd("tests");
    image.cd("images");

    exec->currentIndex = -1;

    exec->currentImagesPath.append(image.absolutePath().append("/image.png"));

    exec->onNextClicked();

    QCOMPARE(exec->ui->previousButton->isEnabled(),true);

    delete dat2d;
    delete exec;
}

void TestExecuteDialog::onPreviousClicked(){
    ExecuteDialog *exec=new ExecuteDialog(0);
    QString datasetName="DatasetProva";
    Dataset2D *dat2d=new Dataset2D(datasetName);
    exec->prepareAnalysis(dat2d,false,false,2,1,2);
    QDir image = QDir::current();
    image.cd("..");
    image.cd("..");
    image.cd("tests");
    image.cd("images");

    exec->currentIndex = 1;

    exec->currentImagesPath.append(image.absolutePath().append("/image.png"));

    exec->onPreviousClicked();

    QCOMPARE(exec->ui->nextButton->isEnabled(),true);

    delete dat2d;
    delete exec;
}

void TestExecuteDialog::onCancelClicked(){
    ExecuteDialog *exec=new ExecuteDialog(0);

    QSignalSpy spy(exec,SIGNAL(abortAnalysis()));

    exec->onCancelClicked();

    QCOMPARE(spy.count(),1);

    delete exec;
}

void TestExecuteDialog::addResultImage(){
    ExecuteDialog *exec=new ExecuteDialog(0);
    QString datasetName="DatasetProva";
    Dataset2D *dat2d=new Dataset2D(datasetName);
    exec->prepareAnalysis(dat2d,false,false,2,1,2);
    QDir image = QDir::current();
    image.cd("..");
    image.cd("..");
    image.cd("tests");
    image.cd("images");

    exec->addResultImage(image.absolutePath().append("/image.png"));

    QCOMPARE(exec->ui->nextButton->isEnabled(),false);

    exec->addResultImage(image.absolutePath().append("/image.png"));

    QCOMPARE(exec->ui->nextButton->isEnabled(),true);

    delete dat2d;
    delete exec;
}

void TestExecuteDialog::onNoFeatureClicked(){
    ExecuteDialog *exec=new ExecuteDialog(0);

    exec->onNoFeatureClicked();

    QCOMPARE(exec->ui->noFeature->isEnabled(),false);

    delete exec;
}

void TestExecuteDialog::onFeatureExtracted(){
    ExecuteDialog *exec=new ExecuteDialog(0);
    QString datasetName="DatasetProva";
    Dataset2D *dat2d=new Dataset2D(datasetName);
    exec->prepareAnalysis(dat2d,false,true,2,1,2);
    QDir image = QDir::current();
    image.cd("..");
    image.cd("..");
    image.cd("tests");
    image.cd("images");

    int progress = exec->ui->progressBar->value();

    exec->onFeatureExtracted(image.absolutePath().append("/image.png"));

    QCOMPARE(exec->ui->progressBar->value(),progress+1);

    exec->prepareAnalysis(dat2d,false,false,2,1,2);

    exec->onFeatureExtracted(image.absolutePath().append("/image.png"));

    QCOMPARE(exec->ui->progressBar->value(),progress+1);

    delete dat2d;
    delete exec;
}


void TestExecuteDialog::onAlgorithmExecuted(){
    ExecuteDialog *exec=new ExecuteDialog(0);
    QString datasetName="DatasetProva";
    Dataset2D *dat2d=new Dataset2D(datasetName);
    exec->prepareAnalysis(dat2d,false,true,2,1,2);
    QDir image = QDir::current();
    image.cd("..");
    image.cd("..");
    image.cd("tests");
    image.cd("images");

    int progress = exec->ui->progressBar->value();

    exec->onAlgorithmExecuted(image.absolutePath().append("/image.png"));

    QCOMPARE(exec->ui->progressBar->value(),progress+1);

    exec->prepareAnalysis(dat2d,false,false,2,1,2);

    exec->onAlgorithmExecuted(image.absolutePath().append("/image.png"));

    QCOMPARE(exec->ui->progressBar->value(),progress+1);

    delete dat2d;
    delete exec;
}

