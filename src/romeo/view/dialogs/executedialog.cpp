#include "executedialog.h"
#include "ui_executedialog.h"
#include <QCloseEvent>
#include <QDebug>
using namespace romeo::view::dialogs;
ExecuteDialog::ExecuteDialog(QWidget *parent) :
    QDialog(parent),currentDataset(0), visualizeFeatures(false), visualizeResults(false),
    currentIndex(0), nImagesPerSubject(0), nSubjects(0),
    ui(new Ui::ExecuteDialog)
{
    ui->setupUi(this);
   connectUI();
}


void ExecuteDialog::connectUI(){
     connect(ui->cancelButton,SIGNAL(clicked()),this,SLOT(onCancelClicked()));
     connect(ui->closeButton,SIGNAL(clicked()),this,SLOT(accept()));
     connect(ui->nextButton,SIGNAL(clicked()),this,SLOT(onNextClicked()));
     connect(ui->previousButton,SIGNAL(clicked()),this,SLOT(onPreviousClicked()));

}

ExecuteDialog::~ExecuteDialog()
{
    delete ui;
}

void ExecuteDialog::closeEvent(QCloseEvent *event) {
if(!ui->closeButton->isEnabled())
    event->ignore(); // keep window
else
    event->accept();
}

void ExecuteDialog::prepareAnalysis(romeo::model::datasets::AbstractDataset *dataset, bool viewResults, bool viewFeatures,int numberSubjects,int nImages)
{

    if(currentDataset != 0 ){
        disconnect(currentDataset,SIGNAL(analysisFinished()),this,SLOT(analysisFinished()));
        if(visualizeResults){
            disconnect(currentDataset,SIGNAL(algorithmExecuted(QString)),this,SLOT(addResultImage(QString)));
        }
        if(visualizeFeatures){
            disconnect(currentDataset,SIGNAL(featureExtracted(QString)),this,SLOT(addResultImage(QString)));
        }
    }

    currentImagesPath.clear();
    currentDataset = dataset;
    visualizeResults = viewResults;
    visualizeFeatures = viewFeatures;
    nSubjects = numberSubjects;
    nImagesPerSubject = nImages;


    connect(currentDataset,SIGNAL(analysisFinished()),this,SLOT(analysisFinished()));
    if(visualizeResults){
        connect(currentDataset,SIGNAL(algorithmExecuted(QString)),this,SLOT(addResultImage(QString)));
    }
    if(visualizeFeatures){
        connect(currentDataset,SIGNAL(featureExtracted(QString)),this,SLOT(addResultImage(QString)));
    }

    ui->subjectsLabel->setText("Number of subjects:" + QString::number(nSubjects));
    ui->statusLabel->setText("Images: 0/"+ QString::number(nSubjects * nImagesPerSubject));
    ui->currentLabel->setText("Executing");
    ui->progressBar->setMaximum(0);
    ui->progressBar->setMaximum(nSubjects * nImagesPerSubject);
    ui->progressBar->setValue(0);
    ui->nextButton->setEnabled(false);
    ui->previousButton->setEnabled(false);
    ui->closeButton->setEnabled(false);
    ui->cancelButton->setEnabled(true);

    ui->widget->setHidden(true);
    qDebug() << "FINISH PREPARE";
}



void ExecuteDialog::addResultImage(QString pathToResult){

    currentImagesPath.append(pathToResult);
    ui->nextButton->setEnabled(true);
    if(currentImagesPath.size() == 1){
        showImage(currentImagesPath[0]);
    }

   ui->progressBar->setValue(ui->progressBar->value()+1);
   ui->statusLabel->setText("Images: " + QString::number(ui->progressBar->value()) + "/"+ QString::number(nSubjects * nImagesPerSubject));

}

void ExecuteDialog::analysisFinished(){
    if(ui->currentLabel->text()  == "Aborting analysis")
        ui->currentLabel->setText("Aborted");
    if(ui->currentLabel->text() == "Executing")
        ui->currentLabel->setText("Finished");

    ui->closeButton->setEnabled(false);
}

void ExecuteDialog::onNextClicked(){
    ui->previousButton->setEnabled(true);
    ++currentIndex;
    if(currentIndex == ui->progressBar->value()){
        ui->nextButton->setEnabled(false);
    }

    showImage(currentImagesPath[currentIndex]);
}


void ExecuteDialog::onPreviousClicked(){
    ui->nextButton->setEnabled(true);
    --currentIndex;
    if(currentIndex == 0){
        ui->previousButton->setEnabled(false);
    }

    showImage(currentImagesPath[currentIndex]);


}

void ExecuteDialog::onCancelClicked(){
    ui->cancelButton->setEnabled(false);
    ui->statusLabel->setText("Aborting analysis");
    emit abortAnalysis();
}


void ExecuteDialog::clearDialog(){

}


void ExecuteDialog::showImage(QString pathToImage){
    //AH BEH
}
