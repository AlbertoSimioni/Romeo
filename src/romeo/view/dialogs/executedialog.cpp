/**
* \file executedialog.cpp
* \author Alessandro Strenghetto
* \date 2014-02-17
**
* \brief Header della classe ExecuteDialog del package romeo::view::dialogs
*/


#include "executedialog.h"
#include "ui_executedialog.h"
#include <src/romeo/model/protocols/color.h>

//QT

#include <QCloseEvent>
#include <QDebug>
#include <QDir>
#include <QMessageBox>

//ITK

#include "itkRGBPixel.h"
#include "itkImage.h"
#include "itkImageFileReader.h"
#include "itkImageToVTKImageFilter.h"

//VTK

#include <vtkRenderWindowInteractor.h>
#include "vtkRenderWindow.h"
#include "vtkRenderer.h"

#include "vtkSmartVolumeMapper.h"
#include "vtkPiecewiseFunction.h"
#include "vtkVolumeProperty.h"
#include "vtkFixedPointVolumeRayCastMapper.h"
#include "vtkInteractorObserver.h"

using namespace romeo::model::protocols;
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
    if(!ui->closeButton->isEnabled()){
        event->ignore(); // keep window
        QMessageBox msgBox;
        msgBox.setText("The analysis are executing.");
        msgBox.setInformativeText("Clicking on the OK button will close the program");
        msgBox.setStandardButtons(QMessageBox::Cancel| QMessageBox::Ok);
        msgBox.setDefaultButton(QMessageBox::Cancel);
        msgBox.setIcon(QMessageBox::Critical);
        int ret = msgBox.exec();

        switch (ret) {
          case QMessageBox::Cancel:
            event->ignore();
              break;
          case QMessageBox::Ok:
            {
            emit forceAbortAnalysis();
            event->accept();
            QCoreApplication::exit(0);
            }
              break;
        }

    }
    else{
        event->accept();
        image_view->GetRenderer()->Clear();
    }
}

void ExecuteDialog::prepareAnalysis(romeo::model::datasets::AbstractDataset *dataset, bool viewResults, bool viewFeatures,int numberSubjects,int nAlgorithm,int nFeatures)
{

    if(currentDataset != 0 ){
        disconnect(currentDataset,SIGNAL(analysisFinished()),this,SLOT(analysisFinished()));
        disconnect(currentDataset,SIGNAL(algorithmExecuted(QString)),this,SLOT(onAlgorithmExecuted(QString)));
        disconnect(currentDataset,SIGNAL(featureExtracted(QString)),this,SLOT(onFeatureExtracted(QString)));
        disconnect(currentDataset,SIGNAL(analysisProblem(QString)),this,SLOT(onAnalysisProblem(QString)));

    }


    currentDataset = dataset;
    visualizeResults = viewResults;
    visualizeFeatures = viewFeatures;
    nSubjects = numberSubjects;
    nImagesPerSubject = nFeatures + nAlgorithm;


    connect(currentDataset,SIGNAL(analysisFinished()),this,SLOT(analysisFinished()));

    connect(currentDataset,SIGNAL(algorithmExecuted(QString)),this,SLOT(onAlgorithmExecuted(QString)));
    connect(currentDataset,SIGNAL(featureExtracted(QString)),this,SLOT(onFeatureExtracted(QString)));
    connect(currentDataset,SIGNAL(analysisProblem(QString)),this,SLOT(onAnalysisProblem(QString)));


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
    imagesFromAlgorithm.clear();
    currentIndex = 0;
    ui->subjectsLabel->setText("Total Subjects: " + QString::number(nSubjects));
    if(visualizeFeatures){
        ui->statusLabel->setText("Total Images: "+ QString::number(nSubjects * nImagesPerSubject));
    }

    else if(visualizeResults) ui->statusLabel->setText("Total Images: "+ QString::number(nSubjects));
    else ui->statusLabel->setText("Total Images: 0");
    ui->currentLabel->setText("Executing");
    ui->nameLabel->setText(QString(""));
    ui->progressBar->setMinimum(0);
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
        showImage(currentImagesPath[0],imagesFromAlgorithm[0]);
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
        imagesFromAlgorithm.append(false);
        addResultImage(pathToFeature);
        ui->statusLabel->setText("Images: " + QString::number(currentIndex+1)+  "/" + QString::number(currentImagesPath.size()));
    }
    ui->progressBar->setValue(ui->progressBar->value()+1);

}

void ExecuteDialog::onAlgorithmExecuted(QString pathToAlgorithm){
    if(visualizeResults){
        imagesFromAlgorithm.append(true);
        addResultImage(pathToAlgorithm);
        ui->statusLabel->setText("Images: " + QString::number(currentIndex+1)+  "/" + QString::number(currentImagesPath.size()));
    }
    ui->progressBar->setValue(ui->progressBar->value()+1);

}


void ExecuteDialog::onNextClicked(){
    ui->previousButton->setEnabled(true);
    ++currentIndex;
    if(currentIndex == currentImagesPath.size()-1){
        ui->nextButton->setEnabled(false);
    }

    showImage(currentImagesPath[currentIndex],imagesFromAlgorithm[currentIndex]);
    ui->statusLabel->setText("Images: " + QString::number(currentIndex+1)+  "/" + QString::number(currentImagesPath.size()));
}


void ExecuteDialog::onPreviousClicked(){
    ui->nextButton->setEnabled(true);
    --currentIndex;
    if(currentIndex == 0){
        ui->previousButton->setEnabled(false);
    }

    showImage(currentImagesPath[currentIndex], imagesFromAlgorithm[currentIndex]);
    ui->statusLabel->setText("Images: " + QString::number(currentIndex+1)+  "/" + QString::number(currentImagesPath.size()));
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

void ExecuteDialog::addAllClusterColors(vtkSmartPointer<vtkDiscretizableColorTransferFunction>& colorPointer) {
    //int order[10] = {1,0,5,9,2,7,3,4,8,6};
    for(int i=0;i<10;i++) {
        int* firstColor = Color::getColor(i);
        double firstColorValue = Color::getSingleValueColor(i);
        colorPointer->AddRGBPoint(firstColorValue,static_cast<double>(firstColor[0])/255,static_cast<double>(firstColor[1])/255,static_cast<double>(firstColor[2])/255);
        //colorPointer->SetIndexedColor(firstColorValue,static_cast<double>(firstColor[0])/255,static_cast<double>(firstColor[1])/255,static_cast<double>(firstColor[2])/255);
    }
    // ultimo colore
    /*int* color = Color::getColor(9);
    double colorValue = Color::getSingleValueColor(9);
    colorPointer->AddRGBSegment(colorValue-1,static_cast<double>(color[0])/255,static_cast<double>(color[1])/255,static_cast<double>(color[2])/255,255.0,1.0,1.0,1.0);*/
}

void ExecuteDialog::showImage(QString pathToImage, bool isAlg){
    ui->widget->setHidden(false);
    if(currentDataset->getType() == TYPE2D ||(currentDataset->getType() ==  TYPE2DT )){


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
        vtkSmartPointer<vtkImageData> image = vtkImageData::New();
        image->DeepCopy(connector->GetOutput());


        //set VTK Viewer to QVTKWidget in Qt's UI

        ui->widget->SetRenderWindow(image_view->GetRenderWindow());

        image_view->SetInputData( image );
        image_view->GetRenderer()->SetBackground(255,255,255);
        image_view->Render();
        image_view->GetRenderer()->ResetCamera();
        image_view->Render();
        ui->widget->update();

    }
    else{
        /*if(!isAlg)
            showImage3DFeature(pathToImage);
        else
            showImage3DCluster(pathToImage);*/
        typedef itk::Image< double, 3> myInputImageType;//Image Type
        typedef itk::ImageFileReader< myInputImageType >  myReaderType;//Reader of Image Type
        myReaderType::Pointer reader = myReaderType::New();

        reader->SetFileName(pathToImage.toStdString() );

        //Exceptional handling
        try {
            reader->Update();
        }
        catch (itk::ExceptionObject & e) {
        }

        ui->nameLabel->setText(pathToImage.split(QDir::toNativeSeparators("/")).takeLast());
        myInputImageType::Pointer input = reader->GetOutput();

        /*itk::ImageRegionIterator<myInputImageType> iterator(input,input->GetLargestPossibleRegion());
        while(!iterator.IsAtEnd()) {
            if(iterator.Get() != 0.0)
                qDebug() << QString::number(iterator.Get());
            ++iterator;
        }*/

        typedef itk::ImageToVTKImageFilter<myInputImageType> myConnectorType;
        myConnectorType::Pointer connector= myConnectorType::New();
        connector->SetInput( input );//Set ITK reader Output to connector you can replace it with filter

        //Exceptional handling
        try {
            connector->Update();
        }
        catch (itk::ExceptionObject & e) {
        }

        vtkSmartPointer<vtkImageData> imageData = vtkSmartPointer<vtkImageData>::New();
        imageData->DeepCopy(connector->GetOutput());

        // itera sull'immagine per trovare min e max
        double min,max;
        if(!isAlg) {
            int* dims = imageData->GetDimensions();
            for (int z = 0; z < dims[2]; z++) {
                for (int y = 0; y < dims[1]; y++) {
                    for (int x = 0; x < dims[0]; x++) {
                        double* pixel = static_cast<double*>(imageData->GetScalarPointer(x,y,z));
                        if(z==0 && y==0 && x==0) {
                            min = pixel[0];
                            max = pixel[0];
                        }
                        else {
                            if(min > pixel[0])
                                min = pixel[0];
                            else {
                                if(max < pixel[0])
                                    max = pixel[0];
                            }
                        }
                    }
                }
            }
        }

        /*if(isAlg) {
            double known[10];
            int index = 0;
            // itero sull'immagine
            int* dims = imageData->GetDimensions();
            for (int z = 0; z < dims[2]; z++)
            {
                for (int y = 0; y < dims[1]; y++)
                {
                    for (int x = 0; x < dims[0]; x++)
                    {
                        double* pixel = static_cast<double*>(imageData->GetScalarPointer(x,y,z));
                        if(index==0) {
                            known[0] = pixel[0];
                            index++;
                            qDebug() << QString::number(pixel[0]);
                        }
                        else {
                            bool found = false;
                            for(int i=0;i<index && !found;i++) {
                                if(pixel[0]==known[i])
                                    found = true;
                            }
                            if(!found) {
                                known[index] = pixel[0];
                                ++index;
                                qDebug() << QString::number(pixel[0]);
                            }
                        }
                    }
                }
            }
        }*/

        vtkSmartPointer<vtkRenderWindow> renWin = vtkSmartPointer<vtkRenderWindow>::New();
        vtkSmartPointer<vtkRenderer> ren1 = vtkSmartPointer<vtkRenderer>::New();
        ren1->SetBackground(1,1,1);
        // background arancione
        //ren1->SetBackground(1,0.3,0);
        // o.1 0.4 0.2
        renWin->AddRenderer(ren1);
        renWin->SetSize(301,300); // intentional odd and NPOT  width/height

        ui->widget->SetRenderWindow(renWin);
        ui->widget->GetInteractor()->SetDesiredUpdateRate(10);
        ui->widget->GetInteractor()->GetInteractorStyle()->SetDefaultRenderer(ren1);
        renWin->Render(); // make sure we have an OpenGL context.

        /*vtkSmartPointer<vtkSmartVolumeMapper> volumeMapper = vtkSmartPointer<vtkSmartVolumeMapper>::New();
        volumeMapper->SetBlendModeToComposite(); // composite first
        volumeMapper->SetInputData(imageData);*/
        /*vtkSmartPointer<vtkVolumeProperty> volumeProperty = vtkSmartPointer<vtkVolumeProperty>::New();
        volumeProperty->ShadeOff();
        volumeProperty->SetInterpolationType(VTK_LINEAR_INTERPOLATION);*/

        vtkSmartPointer<vtkFixedPointVolumeRayCastMapper> volumeMapper = vtkSmartPointer<vtkFixedPointVolumeRayCastMapper>::New();
        volumeMapper->SetBlendModeToComposite(); // composite first
        volumeMapper->SetInputData(imageData);

        vtkSmartPointer<vtkVolumeProperty> volumeProperty = vtkSmartPointer<vtkVolumeProperty>::New();
        volumeProperty->SetIndependentComponents(true);
        //volumeProperty->SetInterpolationTypeToLinear();
        volumeProperty->ShadeOff();
        volumeProperty->SetInterpolationType(VTK_LINEAR_INTERPOLATION);

        vtkSmartPointer<vtkPiecewiseFunction> compositeOpacity = vtkSmartPointer<vtkPiecewiseFunction>::New();
        /*compositeOpacity->AddPoint(0.0,0.0);
        compositeOpacity->AddPoint(80.0,1.0);
        compositeOpacity->AddPoint(80.1,0.0);
        compositeOpacity->AddPoint(255.0,0.0);*/
        if(isAlg) {
            // con valore 1.0, il valore viene visualizzato
            // con valore 0.0, il valore diventa trasparente
            // dunque, fino a 50.575 voglio trasparente
            // poi voglio colorato
            compositeOpacity->AddSegment(0.0,0.0,0.1,0.0);
            compositeOpacity->AddSegment(0.2,1.0,255.0,1.0);
        }
        else {
            // vorrei tutti i valori mostrati, ma quelli che appartengono alla maschera vanno messi trasparenti
            compositeOpacity->AddSegment(min,1.0,max,1.0);
            compositeOpacity->AddPoint(0.0,0.0);
        }
        volumeProperty->SetScalarOpacity(compositeOpacity); // composite first.

        if(isAlg) {
            vtkSmartPointer<vtkDiscretizableColorTransferFunction> color = vtkSmartPointer<vtkDiscretizableColorTransferFunction>::New();
            color->DiscretizeOn();
            color->SetNumberOfValues(10);
            //color->IndexedLookupOn();
            color->SetColorSpaceToRGB();
            // ci interessa mappare solo i valori possibili dei cluster
            addAllClusterColors(color);
            color->Build();
            volumeProperty->SetColor(color);
        }
        else {
            vtkSmartPointer<vtkColorTransferFunction> color = vtkSmartPointer<vtkColorTransferFunction>::New();
            color->SetColorSpaceToRGB();
            // mappiamo tutti i valori da min a max
            //color->AddRGBPoint(0.0  ,0.0,0.0,1.0);
            //color->AddRGBPoint(40.0  ,1.0,0.0,0.0);
            color->AddRGBSegment(min,0.0,0.0,0.0,max,1.0,1.0,1.0);
            //color->AddRGBPoint(min  ,0.0,0.0,0.0);
            //color->AddRGBPoint(max  ,1.0,1.0,1.0);
            color->Build();
            volumeProperty->SetColor(color);
        }
        //color->AddRGBPoint(255.0,1.0,1.0,1.0);

        vtkSmartPointer<vtkVolume> volume = vtkSmartPointer<vtkVolume>::New();
        volume->SetMapper(volumeMapper);
        volume->SetProperty(volumeProperty);

        ren1->AddViewProp(volume);
        //ren1->AddVolume(volume);
        ren1->ResetCamera();

        // Render composite. In default mode. For coverage.
        renWin->Render();

        // 3D texture mode. For coverage.
        //volumeMapper->SetRequestedRenderModeToRayCastAndTexture();
        renWin->Render();

        // Software mode, for coverage. It also makes sure we will get the same
        // regression image on all platforms.
        //volumeMapper->SetRequestedRenderModeToRayCast();
        renWin->Render();
        ui->widget->update();
    }

}
romeo::model::datasets::AbstractDataset *ExecuteDialog::getCurrentDataset() const
{
    return currentDataset;
}

void ExecuteDialog::onAnalysisProblem(QString messageError){
    QMessageBox msgBox;
    msgBox.setIcon(QMessageBox::Critical);
    msgBox.setText("ERR 0x7A2B23C");
    msgBox.setInformativeText(messageError);
    msgBox.exec();
}


void ExecuteDialog::setCurrentDataset(romeo::model::datasets::AbstractDataset *value)
{
    currentDataset = value;
}

