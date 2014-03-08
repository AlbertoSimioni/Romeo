#include "executedialog.h"
#include "ui_executedialog.h"
#include <QCloseEvent>
#include <QDebug>
#include <QDir>

//ITK

#include "itkRGBPixel.h"
#include "itkImage.h"
#include "itkImageFileReader.h"
#include "itkImageToVTKImageFilter.h"
#include "itkMedianImageFilter.h"

#include <vtkRenderWindowInteractor.h>
#include "vtkRenderWindow.h"
#include "vtkRenderer.h"

using namespace romeo::view::dialogs;
using namespace romeo::model;


ExecuteDialog::ExecuteDialog(QWidget *parent) :
    QDialog(parent),currentDataset(0), visualizeFeatures(false), visualizeResults(false),
    currentIndex(0), nImagesPerSubject(0), nSubjects(0),
    ui(new Ui::ExecuteDialog)
{
   image_view = vtkSmartPointer<vtkImageViewer2>::New();

   ui->setupUi(this);
   connectUI();
}


void ExecuteDialog::connectUI(){
     connect(ui->cancelButton,SIGNAL(clicked()),this,SLOT(onCancelClicked()));
     connect(ui->closeButton,SIGNAL(clicked()),this,SLOT(accept()));
     connect(ui->nextButton,SIGNAL(clicked()),this,SLOT(onNextClicked()));
     connect(ui->previousButton,SIGNAL(clicked()),this,SLOT(onPreviousClicked()));
     connect(ui->noFeature,SIGNAL(clicked()),this,SLOT(onNoFeatureClicked()));

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

void ExecuteDialog::prepareAnalysis(romeo::model::datasets::AbstractDataset *dataset, bool viewResults, bool viewFeatures,int numberSubjects,int nAlgorithm,int nFeatures)
{

    if(currentDataset != 0 ){
        disconnect(currentDataset,SIGNAL(analysis()),this,SLOT(analysisFinished()));
        disconnect(currentDataset,SIGNAL(algorithmExecuted(QString)),this,SLOT(onAlgorithmExecuted(QString)));
        connect(currentDataset,SIGNAL(featureExtracted(QString)),this,SLOT(onFeatureExtracted(QString)));
    }


    currentDataset = dataset;
    visualizeResults = viewResults;
    visualizeFeatures = viewFeatures;
    nSubjects = numberSubjects;
    nImagesPerSubject = nFeatures + nAlgorithm;


    connect(currentDataset,SIGNAL(analysisFinished()),this,SLOT(analysisFinished()));

    connect(currentDataset,SIGNAL(algorithmExecuted(QString)),this,SLOT(onAlgorithmExecuted(QString)));
    connect(currentDataset,SIGNAL(featureExtracted(QString)),this,SLOT(onFeatureExtracted(QString)));
    clearDialog();

}

void ExecuteDialog::clearDialog(){
    if(visualizeFeatures){
        ui->noFeature->setEnabled(true);
    }
    else{
        ui->noFeature->setEnabled(false);
    }
    currentImagesPath.clear();
    currentIndex = 0;
    ui->subjectsLabel->setText("Total Subjects: " + QString::number(nSubjects));
    ui->statusLabel->setText("Total Images: "+ QString::number(nSubjects * nImagesPerSubject));
    ui->currentLabel->setText("Executing");
    ui->nameLabel->setText(QString(""));
    ui->progressBar->setMaximum(0);
    ui->progressBar->setMaximum(nSubjects * nImagesPerSubject);
    ui->progressBar->setValue(0);
    ui->nextButton->setEnabled(false);
    ui->previousButton->setEnabled(false);
    ui->closeButton->setEnabled(false);
    ui->cancelButton->setEnabled(true);

    ui->widget->setHidden(true);
}

void ExecuteDialog::addResultImage(QString pathToResult){

    currentImagesPath.append(pathToResult);

    if(currentImagesPath.size() == 1)
        showImage(currentImagesPath[0]);
    else
       ui->nextButton->setEnabled(true);
}

void ExecuteDialog::analysisFinished(){
    if(ui->progressBar->value() == (nImagesPerSubject * nSubjects))
        ui->currentLabel->setText("Completed");
    else
        ui->currentLabel->setText("Aborted");
    ui->cancelButton->setEnabled(false);
    ui->closeButton->setEnabled(true);
}


void ExecuteDialog::onFeatureExtracted(QString pathToFeature){
    if(visualizeFeatures){
        addResultImage(pathToFeature);
    }
    ui->progressBar->setValue(ui->progressBar->value()+1);
    ui->statusLabel->setText("Images: " + QString::number(ui->progressBar->value()) + "/"+ QString::number(nSubjects * nImagesPerSubject));
}

void ExecuteDialog::onAlgorithmExecuted(QString pathToAlgorithm){
    if(visualizeResults){
        addResultImage(pathToAlgorithm);
    }
    ui->progressBar->setValue(ui->progressBar->value()+1);
    ui->statusLabel->setText("Images: " + QString::number(ui->progressBar->value()) + "/"+ QString::number(nSubjects * nImagesPerSubject));
}


void ExecuteDialog::onNextClicked(){
    ui->previousButton->setEnabled(true);
    ++currentIndex;
    if(currentIndex == currentImagesPath.size()-1){
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
    ui->currentLabel->setText("Aborting analysis");
    emit abortAnalysis();
}


void ExecuteDialog::onNoFeatureClicked(){
    visualizeFeatures = false;
    ui->noFeature->setEnabled(false);
}


void ExecuteDialog::showImage(QString pathToImage){

    if(currentDataset->getType() == TYPE2D ||(currentDataset->getType() ==  TYPE2DT )){

    ui->widget->setHidden(false);
    typedef itk::RGBPixel<unsigned char> myRGBPixelType;//Pixel Type
    typedef itk::Image< myRGBPixelType, 2> myInputImageType;//Image Type
    typedef itk::ImageFileReader< myInputImageType >  myReaderType;//Reader of Image Type
    myReaderType::Pointer reader = myReaderType::New();


    reader->SetFileName( pathToImage.toStdString() );
    //Exceptional handling
    try {
        reader->Update();
    }
    catch (itk::ExceptionObject & e) {
    }

    ui->nameLabel->setText(pathToImage.split(QDir::toNativeSeparators("/")).takeLast());
    myInputImageType::Pointer input = reader->GetOutput();

    typedef itk::ImageToVTKImageFilter<myInputImageType> myConnectorType;
    myConnectorType::Pointer connector= myConnectorType::New();
    connector->SetInput( input );//Set ITK reader Output to connector you can replace it with filter

    //Exceptional handling
    try {
        connector->Update();
    }
    catch (itk::ExceptionObject & e) {
    }


    //deep copy connector's output to an image else connector will go out of scope
    //and vanish it will cause error while changing slice
    vtkImageData * image = vtkImageData::New();
    image->DeepCopy(connector->GetOutput());


    //ui->widget->resize(dims[0],dims[1]);
    //image_view->SetSize(dims[0],dims[1]);
    //set VTK Viewer to QVTKWidget in Qt's UI
    ui->widget->SetRenderWindow(image_view->GetRenderWindow());
    //image_view->SetupInteractor(ui->widget->GetRenderWindow()->GetInteractor());
    //Set input image to VTK viewer
    image_view->SetInputData( image );
    //image_view->SetSlice(0);
    image_view->Render();
    image_view->GetRenderer()->ResetCamera();
    image_view->Render();

    ui->widget->update();

    }

}
