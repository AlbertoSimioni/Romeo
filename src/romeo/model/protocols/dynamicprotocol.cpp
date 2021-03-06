/**
* \file dynamicprotocol.cpp
* \author Matteo Pozza
* \date 2014-02-17
**
* \brief Header della classe DynamicProtocol del package romeo::model::protocols
*/

#include "dynamicprotocol.h"
// QT
#include <QThread>
#include <QLibrary>
#include <QList>
#include <QDir>
#include <QUrl>
// ITK
#include "itkImage.h"
#include "itkRGBPixel.h"
#include "itkNeighborhoodIterator.h"
#include "itkImageLinearConstIteratorWithIndex.h"
#include <opencv2/imgproc/imgproc.hpp>

using namespace romeo::model::protocols;

DynamicProtocol::DynamicProtocol(QString nomeP, QString desc, algorithms::AbstractAlgorithm* alg, int clusterNum, QList<QString> algParameters, QList<features::AbstractFeature*> feat, bool testProtocol, int frameInit, int frameEnd):
    AbstractProtocol(nomeP,desc,alg, clusterNum, algParameters, feat,testProtocol),frameInit(frameInit),frameEnd(frameEnd)
{
}

double** DynamicProtocol::read2DVideo(cv::VideoCapture video) {
    int numberOfPixel = video.get( CV_CAP_PROP_FRAME_WIDTH ) * video.get( CV_CAP_PROP_FRAME_HEIGHT );
    int numberOfFrames = video.get(CV_CAP_PROP_FRAME_COUNT);
    // alloco il risultato
    double** result = new double*[3*numberOfFrames];
    for(int i=0;i<3*numberOfFrames;i++)
        result[i] = new double[numberOfPixel];
    cv::Mat frame;
    int currentFrame = 0;
    while( video.read(frame) ) {
        Image2DType::Pointer itkFrame = itk::OpenCVImageBridge::CVMatToITKImage< Image2DType >( frame );
        itk::ImageRegionIterator<Image2DType> imageIterator(itkFrame , itkFrame->GetLargestPossibleRegion());
        int j=0;
        while(!imageIterator.IsAtEnd()) {
            for(int color=0,i=currentFrame;color<3;color++,i++) {
                result[i][j] = imageIterator.Get()[color];
            }
            ++imageIterator;
            ++j;
        }
        currentFrame += 3;
    }
    return result;
}

double** DynamicProtocol::read3DVideo(Image4DType::Pointer video) {
    int numberOfPixel = video->GetLargestPossibleRegion().GetSize()[0]*video->GetLargestPossibleRegion().GetSize()[1]*video->GetLargestPossibleRegion().GetSize()[2];
    int numberOfFrames = video->GetLargestPossibleRegion().GetSize()[3];
    // alloco il risultato
    double** result = new double*[numberOfPixel];
    for(int i=0;i<numberOfPixel;i++)
        result[i] = new double[numberOfFrames];
    itk::ImageLinearConstIteratorWithIndex<Image4DType> it( video, video->GetLargestPossibleRegion() );
    it.SetDirection( 3 ); // Walk along time dimension
    int i=0;
    while(!it.IsAtEnd()) {
        for(int j=0; j<numberOfFrames;j++) {
            result[i][j] = static_cast<double>(it.Get());
            ++it;
        }
        it.NextLine();
        ++i;
    }
    return result;
}

double** DynamicProtocol::apply2DDynamicFeature(cv::VideoCapture video,Image2DType::Pointer output,Mask2DType::Pointer mask,romeo::model::protocols::features::DynamicFeature* feature) {
    typedef double* (*MyPrototype)(double** data,const int numberOfPixel,int begin,int end);
    MyPrototype featureExtractor = (MyPrototype) QLibrary::resolve(feature->getDynamicLibraryPath(),feature->getDynamicFunctionName().toStdString().c_str());
    if(!featureExtractor){
        // non viene trovata le libreria
        QString message = "Cannot find library " + feature->getDynamicFunctionName() + " located in " + feature->getDynamicLibraryPath();
        throw message;
    }
    int numberOfPixel = video.get( CV_CAP_PROP_FRAME_WIDTH ) * video.get( CV_CAP_PROP_FRAME_HEIGHT );
    int numberOfFrames = video.get(CV_CAP_PROP_FRAME_COUNT);
    int currentFrameInit, currentFrameEnd;
    // controllo sugli indici indicati
    if(frameInit == -1 && frameEnd == -1) {
        // vanno presi primo frame e ultimo frame
        currentFrameInit = 0;
        currentFrameEnd = numberOfFrames - 1;
    }
    else {
        // controllo sull'integrità degli indici
        // gli indici segnalati sono sempre +1
        if(frameInit>numberOfFrames || frameEnd>numberOfFrames) {
            // lancia un'eccezione, out of bounds
            throw numberOfFrames;
        }
        else {
            currentFrameInit = frameInit - 1;
            currentFrameEnd = frameEnd - 1;
        }
    }

    // iteratore per l'immagine in output
    itk::ImageRegionIterator<Image2DType> outputIterator(output , output->GetLargestPossibleRegion());

    // iteratore per la maschera
    itk::ImageRegionIterator<Mask2DType> maskIterator;
    // maschera in un array: servirà per createImage
    int* maskArray;
    if(mask.IsNotNull()) {
        maskIterator = itk::ImageRegionIterator<Mask2DType>(mask , mask->GetLargestPossibleRegion());
        maskArray = getMask<Mask2DType::Pointer,Mask2DType>(mask,numberOfPixel);
    }
    else {
        maskArray = new int[numberOfPixel];
        for(int i=0;i<numberOfPixel;i++)
            maskArray[i] = 255;
    }
    // alloco il risultato
    double** result;
    if(feature->getName() == "Value") {
        result = new double*[3*(currentFrameEnd-currentFrameInit+1)];
        for(int i=0;i<3*(currentFrameEnd-currentFrameInit+1);++i)
            result[i] = new double[numberOfPixel];
        int currentFrame = 0;
        for(int color = 0;color<3;color++) {
            video.set(CV_CAP_PROP_POS_AVI_RATIO , 0);
            cv::Mat frame;
            int j=0;
            while( video.read(frame) ) {
                // j è l'indice del frame corrente
                // currentFrame è l'indice dei frame analizzati
                if(j>=currentFrameInit && j<=currentFrameEnd) {
                    Image2DType::Pointer itkFrame = itk::OpenCVImageBridge::CVMatToITKImage< Image2DType >( frame );
                    itk::ImageRegionIterator<Image2DType> imageIterator(itkFrame , itkFrame->GetLargestPossibleRegion());
                    if(mask.IsNotNull()) {
                        maskIterator.GoToBegin();
                        int i = 0;
                        while(!imageIterator.IsAtEnd()) {
                            if(static_cast<int>(maskIterator.Get()) == 0)
                                result[currentFrame][i]=0.0;
                            else
                                result[currentFrame][i]=imageIterator.Get()[color];
                            ++imageIterator;
                            ++maskIterator;
                            ++i;
                        }
                        ++j;
                    }
                    else {
                        int i = 0;
                        while(!imageIterator.IsAtEnd()) {
                            result[currentFrame][i]=imageIterator.Get()[color];
                            ++imageIterator;
                            ++i;
                        }
                        ++j;
                    }
                    ++currentFrame;
                }
                else
                    ++j;
            }
        }
        // creo solo primo frame
        double** image = new double*[3];
        // k deve andare a prendere il frame 0 - (currentFrameEnd-currentFrameInit+1) - etc..
        for(int k=0,j=0;j<3;k += currentFrameEnd-currentFrameInit+1,j++)
            image[j] = result[k];
        // creazione immagine output
        createImage2D(outputIterator,image,maskArray,numberOfPixel);
        // cancella puntatore temporaneo
        delete[] image;
    }
    else {
        result = new double*[3];
        // eseguo ciclo
        for(int color = 0;color<3;color++) {
            // allocazione risultato
            double** matrix = new double*[numberOfPixel];
            for(int i=0;i<numberOfPixel;i++)
                matrix[i] = new double[currentFrameEnd-currentFrameInit+1];
            video.set(CV_CAP_PROP_POS_AVI_RATIO , 0);
            cv::Mat frame;
            int j=0;
            int currentFrame = 0;
            while( video.read(frame) ) {
                // j è l'indice del frame corrente
                // currentFrame è l'indice dei frame analizzati
                if(j>=currentFrameInit && j<=currentFrameEnd) {
                    Image2DType::Pointer itkFrame = itk::OpenCVImageBridge::CVMatToITKImage< Image2DType >( frame );
                    itk::ImageRegionIterator<Image2DType> imageIterator(itkFrame , itkFrame->GetLargestPossibleRegion());
                    if(mask.IsNotNull()) {
                        maskIterator.GoToBegin();
                        int i = 0;
                        while(!imageIterator.IsAtEnd()) {
                            if(static_cast<int>(maskIterator.Get()) == 0)
                                matrix[i][currentFrame]=0.0;
                            else
                                matrix[i][currentFrame]=imageIterator.Get()[color];
                            ++imageIterator;
                            ++maskIterator;
                            ++i;
                        }
                        ++j;
                    }
                    else {
                        int i = 0;
                        while(!imageIterator.IsAtEnd()) {
                            matrix[i][currentFrame]=imageIterator.Get()[color];
                            ++imageIterator;
                            ++i;
                        }
                        ++j;
                    }
                    ++currentFrame;
                }
                else
                    ++j;
            }
            result[color] = featureExtractor(matrix,numberOfPixel,currentFrameInit,currentFrameEnd);
            // delete di matrix
            for(int i=0;i<numberOfPixel;i++)
                delete[] matrix[i];
            delete[] matrix;
        }
        // creazione immagine output
        createImage2D(outputIterator,result,maskArray,numberOfPixel);
    }
    // cancellazione della maschera
    delete[] maskArray;
    // ritorna array di double
    return result;
}

double** DynamicProtocol::apply3DDynamicFeature(Image4DType::Pointer video,Image3DType::Pointer output,Mask3DType::Pointer mask,romeo::model::protocols::features::DynamicFeature* feature) {
    typedef double* (*MyPrototype)(double** data,const int numberOfPixel,int begin,int end);
    MyPrototype featureExtractor = (MyPrototype) QLibrary::resolve(feature->getDynamicLibraryPath(),feature->getDynamicFunctionName().toStdString().c_str());
    if(!featureExtractor){
        // non viene trovata le libreria
        QString message = "Cannot find library " + feature->getDynamicFunctionName() + " located in " + feature->getDynamicLibraryPath();
        throw message;
    }
    int numberOfPixel = video->GetLargestPossibleRegion().GetSize()[0]*video->GetLargestPossibleRegion().GetSize()[1]*video->GetLargestPossibleRegion().GetSize()[2];
    int numberOfFrames = video->GetLargestPossibleRegion().GetSize()[3];
    int currentFrameInit, currentFrameEnd;
    // controllo sugli indici indicati
    if(frameInit == -1 && frameEnd == -1) {
        // vanno presi primo frame e ultimo frame
        currentFrameInit = 0;
        currentFrameEnd = numberOfFrames - 1;
    }
    else {
        // controllo sull'integrità degli indici
        // gli indici segnalati sono sempre +1
        if(frameInit>numberOfFrames || frameEnd>numberOfFrames) {
            // lancia un'eccezione, out of bounds
            throw numberOfFrames;
        }
        else {
            currentFrameInit = frameInit - 1;
            currentFrameEnd = frameEnd - 1;
        }
    }

    // iteratore per l'immagine in output
    itk::ImageRegionIterator<Image3DType> outputIterator(output , output->GetLargestPossibleRegion());

    // iteratore per la maschera
    itk::ImageRegionIterator<Mask3DType> maskIterator;
    // maschera in un array: servirà per createImage
    int* maskArray;
    if(mask.IsNotNull()) {
        maskIterator = itk::ImageRegionIterator<Mask3DType>(mask , mask->GetLargestPossibleRegion());
        maskArray = getMask<Mask3DType::Pointer,Mask3DType>(mask,numberOfPixel);
    }
    else {
        maskArray = new int[numberOfPixel];
        for(int i=0;i<numberOfPixel;i++)
            maskArray[i] = 255;
    }

    itk::ImageLinearConstIteratorWithIndex<Image4DType> it( video, video->GetLargestPossibleRegion() );

    if(feature->getName() == "Value") {
        // alloco il risultato
        double** result;
        result = new double*[currentFrameEnd-currentFrameInit+1];
        for(int i=0;i<(currentFrameEnd-currentFrameInit+1);++i)
            result[i] = new double[numberOfPixel];
        it.SetDirection( 3 ); // Walk along time dimension
        it.GoToBegin();
        if(mask.IsNotNull()) {
            maskIterator.GoToBegin();
            int i = 0;
            while(!it.IsAtEnd()) {
                if(static_cast<int>(maskIterator.Get())==0) {
                    for(int j=0,index=0;j<numberOfFrames;++j,++it) {
                        if(j>=currentFrameInit && j<=currentFrameEnd) {
                            result[index][i]=0.0;
                            ++index;
                        }
                    }
                }
                else {
                    for(int j=0,index=0;j<numberOfFrames;++j,++it) {
                        if(j>=currentFrameInit && j<=currentFrameEnd) {
                            result[index][i]=static_cast<double>(it.Get());
                            ++index;
                        }
                    }
                }
                it.NextLine();
                ++maskIterator;
                ++i;
            }
        }
        else {
            int i = 0;
            while(!it.IsAtEnd()) {
                for(int j=0,index=0;j<numberOfFrames;++j,++it) {
                    if(j>=currentFrameInit && j<=currentFrameEnd) {
                        result[index][i]=static_cast<double>(it.Get());
                        ++index;
                    }
                }
                it.NextLine();
                ++i;
            }
        }
        // creo solo primo frame
        // creazione immagine output
        createImage3D(outputIterator,result[0],maskArray,numberOfPixel);
        // cancellazione della maschera
        delete[] maskArray;
        // ritorna array di double
        return result;
    }
    else {
        // alloco il risultato
        double** result = new double*;
        // allocazione risultato
        double** matrix = new double*[numberOfPixel];
        for(int i=0;i<numberOfPixel;i++)
            matrix[i] = new double[currentFrameEnd-currentFrameInit+1];
        it.SetDirection( 3 ); // Walk along time dimension
        it.GoToBegin();
        if(mask.IsNotNull()) {
            maskIterator.GoToBegin();
            int i = 0;
            while(!it.IsAtEnd()) {
                if(static_cast<int>(maskIterator.Get())==0) {
                    for(int j=0,index=0;j<numberOfFrames;++j,++it) {
                        if(j>=currentFrameInit && j<=currentFrameEnd) {
                            matrix[i][index]=0.0;
                            ++index;
                        }
                    }
                }
                else {
                    for(int j=0,index=0;j<numberOfFrames;++j,++it) {
                        if(j>=currentFrameInit && j<=currentFrameEnd) {
                            matrix[i][index]=static_cast<double>(it.Get());
                            ++index;
                        }
                    }
                }
                it.NextLine();
                ++maskIterator;
                ++i;
            }
        }
        else {
            int i = 0;
            while(!it.IsAtEnd()) {
                for(int j=0,index=0;j<numberOfFrames;++j,++it) {
                    if(j>=currentFrameInit && j<=currentFrameEnd) {
                        matrix[i][index]=static_cast<double>(it.Get());
                        ++index;
                    }
                }
                it.NextLine();
                ++i;
            }
        }
        result[0] = featureExtractor(matrix,numberOfPixel,currentFrameInit,currentFrameEnd);
        // delete di matrix
        for(int i=0;i<numberOfPixel;i++)
            delete[] matrix[i];
        delete[] matrix;
        // creazione immagine output
        createImage3D(outputIterator,result[0],maskArray,numberOfPixel);
        // cancellazione della maschera
        delete[] maskArray;
        // ritorna array di double
        return result;
    }
}

void DynamicProtocol::video2DExecute(romeo::model::datasets::AbstractSubject *subject,QString path,bool saveFeatures,QString outputFormat) {
    // il path viene aggiustato rispetto ai corretti separatori in base al sistema operativo
    path = QDir::toNativeSeparators(path + "/");
    if(outputFormat== "INPUT")
        outputFormat = QString(".") + subject->getSubject().split(".").takeLast();
    romeo::model::imageIO::HandlerIODynamic* videoHandler = romeo::model::imageIO::HandlerIODynamic::getInstance();
    cv::VideoCapture videoCapture = videoHandler->read2DVideo(subject->getSubject());
    Mask2DType::Pointer maskPointer = videoHandler->readImage<Mask2DType::Pointer,Mask2DType>(subject->getMask());
    QList<romeo::model::protocols::features::AbstractFeature*> featureList = getFeatures();
    int numberOfColumns;
    int numberOfRows = videoCapture.get( CV_CAP_PROP_FRAME_WIDTH ) * videoCapture.get( CV_CAP_PROP_FRAME_HEIGHT );
    int numberOfFrames = videoCapture.get(CV_CAP_PROP_FRAME_COUNT);
    double** result;
    if(featureList.size()>0) {
        // ci sono features da estrarre
        int currentFrameInit, currentFrameEnd;
        // controllo sugli indici indicati
        if(frameInit == -1 && frameEnd == -1) {
            // vanno presi primo frame e ultimo frame
            currentFrameInit = 0;
            currentFrameEnd = numberOfFrames - 1;
        }
        else {
            // controllo sull'integrità degli indici
            // gli indici segnalati sono sempre +1
            if(frameInit>numberOfFrames || frameEnd>numberOfFrames) {
                // lancia un'eccezione, out of bounds
                throw numberOfFrames;
            }
            else {
                currentFrameInit = frameInit - 1;
                currentFrameEnd = frameEnd - 1;
            }
        }

        // è necessario controllare se è presente la feature "Value"
        // estimatedColumns mi serve per capire il numero di colonne che al peggio possono essere allocate sullo heap
        int estimatedColumns;
        bool value = false;
        for(int i=0;i<featureList.size() && !value;++i) {
            if(featureList[i]->getName()=="Value")
                value = true;
        }
        if(value) {
            numberOfColumns = 3*(featureList.size()-1) + 3*(currentFrameEnd-currentFrameInit+1);
            // il caso peggiore è:
            // - ho estratto tutte le feature (non contando la value) => 3*(featureList.size()-1)
            // - nell'estrazione dell'ultima feature devo ancora deallocare la matrice utilizzata per il calcolo => (currentFrameEnd-currentFrameInit+1)
            // - ho estratto anche la value => 3*(currentFrameEnd-currentFrameInit+1)
            // oppure
            // - ho estratto tutte le feature e sto facendo la trasposta => numberOfColumns * 2
            int value1 = numberOfColumns + (currentFrameEnd-currentFrameInit+1);
            int value2 = 2*numberOfColumns;
            estimatedColumns = (value1>value2) ? value1 : value2;
        }
        else {
            numberOfColumns = 3*featureList.size();
            // il caso peggiore è:
            // - ho estratto tutte le feature => 3*featureList.size()
            // - nell'estrazione dell'ultima feature devo ancora deallocare la matrice utilizzata per il calcolo => (currentFrameEnd-currentFrameInit+1)
            // oppure
            // - ho estratto tutte le feature e sto facendo la trasposta => numberOfColumns * 2
            int value1 = numberOfColumns + (currentFrameEnd-currentFrameInit+1);
            int value2 = 2*numberOfColumns;
            estimatedColumns = (value1>value2) ? value1 : value2;
        }
        long requestedMemory = numberOfRows*estimatedColumns;
        // se la memoria richiesta è eccessiva lancia una eccezione
        checkRequestedMemory(requestedMemory);
        result = new double*[numberOfColumns];
        int index = 0;
        for(int i=0;i<featureList.size() && !getStopAnalysis();i++) {
            // alloco output
            Image2DType::IndexType startIndex;
            startIndex.Fill(0);
            Image2DType::SizeType regionSize;
            regionSize[0] = videoCapture.get( CV_CAP_PROP_FRAME_WIDTH );
            regionSize[1] = videoCapture.get( CV_CAP_PROP_FRAME_HEIGHT );
            Image2DType::RegionType region(startIndex,regionSize);
            Image2DType::Pointer outputFeature = Image2DType::New();
            outputFeature->SetRegions(region);
            outputFeature->Allocate();
            romeo::model::protocols::features::AbstractFeature* currentFeature = featureList[i];
            double** singleFeature;
            romeo::model::protocols::features::DynamicFeature* dynamicFeature = dynamic_cast<romeo::model::protocols::features::DynamicFeature*>(featureList[i]);
            singleFeature = apply2DDynamicFeature(videoCapture,outputFeature,maskPointer,dynamicFeature);
            // singleFeature è una matrice [ncols][nrows]
            if(featureList[i]->getName()=="Value") {
                for(int j=0;j<(3*(currentFrameEnd-currentFrameInit+1));j++) {
                    result[index]=singleFeature[j];
                    ++index;
                }
            }
            else {
                for(int j=0;j<3;j++) {
                    result[index]=singleFeature[j];
                    ++index;
                }
            }
            if(saveFeatures) {
                QString fileName = QUrl::fromLocalFile(subject->getName() + "_" + currentFeature->getName()).path();
                videoHandler->writeImage<Image2DType::Pointer,Image2DType>(outputFeature,fileName,path,outputFormat);
                emit featureExtracted(path + fileName + outputFormat);
            }
            else{
                emit featureExtracted(QString());
            }
        }
        if(getStopAnalysis()){
           numberOfColumns = index;
        }
    }
    else {
        // non ci sono feature da estrarre, va preparata la matrice con tre colonne sole
        numberOfColumns = 3*numberOfFrames;
        // il caso peggiore è nel momento del calcolo della trasposta
        long requestedMemory = numberOfRows*numberOfColumns*2;
        // se la memoria richiesta è eccessiva lancia una eccezione
        checkRequestedMemory(requestedMemory);
        result = read2DVideo(videoCapture);
    }

    if(numberOfColumns < 3){
       delete[] result;
    }
    else{
        double** transponse;

        transponse = transform(result,numberOfRows,numberOfColumns);

        // transponse è una matrice [nrows][ncols]
        romeo::model::protocols::algorithms::AbstractAlgorithm* algorithmToExecute = getAlgorithm();
        if(algorithmToExecute && !getStopAnalysis()) {
            // c'è effettivamente un algoritmo da eseguire
            // creazione maschera
            int* mask = getMask<Mask2DType::Pointer,Mask2DType>(maskPointer,numberOfRows);
            // creazione clusterid
            int* clusterid = new int[numberOfRows];
            algorithmToExecute->execute(transponse,mask,numberOfRows,numberOfColumns,clusterid,getNClusters(),getAlgorithmParameters());
            // creazione immagine di output
            Image2DType::IndexType startIndex;
            startIndex.Fill(0);
            Image2DType::SizeType regionSize;
            regionSize[0] = videoCapture.get( CV_CAP_PROP_FRAME_WIDTH );
            regionSize[1] = videoCapture.get( CV_CAP_PROP_FRAME_HEIGHT );
            Image2DType::RegionType region(startIndex,regionSize);
            Image2DType::Pointer output = Image2DType::New();
            output->SetRegions(region);
            output->Allocate();
            createClusteringImage<Image2DType::Pointer,Image2DType>(output,clusterid,mask);
            // delete dei dati sullo heap
            delete[] mask;
            delete[] clusterid;
            // scrivi l'immagine
            QString fileName = QUrl::fromLocalFile(subject->getName() + "_" + algorithmToExecute->getName()).path();
            videoHandler->writeImage<Image2DType::Pointer,Image2DType>(output,fileName,path,outputFormat);
            emit algorithmExecuted(path + fileName + outputFormat);
        }
        // delete dei dati
        for(int i=0;i<numberOfRows;i++)
            delete[] transponse[i];
        delete[] transponse;
    }
}

void DynamicProtocol::video3DExecute(romeo::model::datasets::AbstractSubject *subject,QString path,bool saveFeatures,QString outputFormat) {
    // il path viene aggiustato rispetto ai corretti separatori in base al sistema operativo
    path = QDir::toNativeSeparators(path + "/");
    if(outputFormat== "INPUT")
        outputFormat = QString(".") + subject->getSubject().split(".").takeLast();
    romeo::model::imageIO::HandlerIODynamic* videoHandler = romeo::model::imageIO::HandlerIODynamic::getInstance();
    Image4DType::Pointer video = videoHandler->readImage<Image4DType::Pointer,Image4DType>(subject->getSubject());
    Mask3DType::Pointer maskPointer = videoHandler->readImage<Mask3DType::Pointer,Mask3DType>(subject->getMask());
    QList<romeo::model::protocols::features::AbstractFeature*> featureList = getFeatures();
    int numberOfRows = video->GetLargestPossibleRegion().GetSize()[0]*video->GetLargestPossibleRegion().GetSize()[1]*video->GetLargestPossibleRegion().GetSize()[2];
    int numberOfFrames = video->GetLargestPossibleRegion().GetSize()[3];
    int numberOfColumns;
    double** result;
    if(featureList.size()>0) {
        int currentFrameInit, currentFrameEnd;
        // controllo sugli indici indicati
        if(frameInit == -1 && frameEnd == -1) {
            // vanno presi primo frame e ultimo frame
            currentFrameInit = 0;
            currentFrameEnd = numberOfFrames - 1;
        }
        else {
            // controllo sull'integrità degli indici
            // gli indici segnalati sono sempre +1
            if(frameInit>numberOfFrames || frameEnd>numberOfFrames) {
                // lancia un'eccezione, out of bounds
                throw numberOfFrames;
            }
            else {
                currentFrameInit = frameInit - 1;
                currentFrameEnd = frameEnd - 1;
            }
        }
        // è necessario controllare se è presente la feature "Value"
        // estimatedColumns mi serve per capire il numero di colonne che al peggio possono essere allocate sullo heap
        int estimatedColumns;
        bool value = false;
        for(int i=0;i<featureList.size() && !value;++i) {
            if(featureList[i]->getName()=="Value")
                value = true;
        }
        if(value) {
            numberOfColumns = (featureList.size()-1) + (currentFrameEnd-currentFrameInit+1);
            // il caso peggiore è:
            // - ho estratto tutte le feature (non contando la value) => (featureList.size()-1)
            // - nell'estrazione dell'ultima feature devo ancora deallocare la matrice utilizzata per il calcolo => (currentFrameEnd-currentFrameInit+1)
            // - ho estratto anche la value => (currentFrameEnd-currentFrameInit+1)
            // oppure
            // - ho estratto tutte le feature e sto facendo la trasposta => numberOfColumns * 2
            int value1 = numberOfColumns + (currentFrameEnd-currentFrameInit+1);
            int value2 = 2*numberOfColumns;
            estimatedColumns = (value1>value2) ? value1 : value2;
        }
        else {
            numberOfColumns = featureList.size();
            // il caso peggiore è:
            // - ho estratto tutte le feature (non contando la value) => featureList.size()
            // - nell'estrazione dell'ultima feature devo ancora deallocare la matrice utilizzata per il calcolo => (currentFrameEnd-currentFrameInit+1)
            // oppure
            // - ho estratto tutte le feature e sto facendo la trasposta => numberOfColumns * 2
            int value1 = numberOfColumns + (currentFrameEnd-currentFrameInit+1);
            int value2 = 2*numberOfColumns;
            estimatedColumns = (value1>value2) ? value1 : value2;
        }
        long requestedMemory = numberOfRows*estimatedColumns;
        // se la memoria richiesta è eccessiva lancia una eccezione
        checkRequestedMemory(requestedMemory);
        result = new double*[numberOfColumns];
        int index = 0;
        for(int i=0;i<featureList.size() && !getStopAnalysis();i++) {
            // alloco immagine output
            Image3DType::IndexType startIndex;
            startIndex.Fill(0);
            Image3DType::SizeType regionSize;
            regionSize[0] = video->GetLargestPossibleRegion().GetSize()[0];
            regionSize[1] = video->GetLargestPossibleRegion().GetSize()[1];
            regionSize[2] = video->GetLargestPossibleRegion().GetSize()[2];
            Image3DType::RegionType region(startIndex,regionSize);
            Image3DType::Pointer outputFeature = Image3DType::New();
            outputFeature->SetRegions(region);
            outputFeature->Allocate();
            romeo::model::protocols::features::AbstractFeature* currentFeature = featureList[i];
            double** singleFeature;
            romeo::model::protocols::features::DynamicFeature* dynamicFeature = dynamic_cast<romeo::model::protocols::features::DynamicFeature*>(featureList[i]);
            singleFeature = apply3DDynamicFeature(video,outputFeature,maskPointer,dynamicFeature);
            // singleFeature è una matrice [ncols][nrows]
            if(featureList[i]->getName()=="Value") {
                for(int j=0;j<(currentFrameEnd-currentFrameInit+1);j++) {
                    result[index]=singleFeature[j];
                    ++index;
                }
            }
            else {
                result[index]=singleFeature[0];
                ++index;
            }
            if(saveFeatures) {
                QString fileName = QUrl::fromLocalFile(subject->getName() + "_" + currentFeature->getName()).path();
                videoHandler->writeImage<Image3DType::Pointer,Image3DType>(outputFeature,fileName,path,outputFormat);
                emit featureExtracted(path + fileName + outputFormat);
            }
            else{
                emit featureExtracted(QString());
            }
        }
        if(getStopAnalysis()){
           numberOfColumns = index;
        }
    }
    else {
        numberOfColumns = numberOfFrames;
        // il caso peggiore è nel momento della trasposta
        long requestedMemory = 2*numberOfRows*numberOfColumns;
        // se la memoria richiesta è eccessiva lancia una eccezione
        checkRequestedMemory(requestedMemory);
        result = read3DVideo(video);
    }

    if(numberOfColumns < 1){
       delete[] result;
    }
    else{
        double** transponse;

        transponse = transform(result,numberOfRows,numberOfColumns);

        // transponse è una matrice [nrows][ncols]
        romeo::model::protocols::algorithms::AbstractAlgorithm* algorithmToExecute = getAlgorithm();
        if(algorithmToExecute && !getStopAnalysis()) {
            // c'è effettivamente un algoritmo da eseguire
            // creazione maschera
            int* mask = getMask<Mask3DType::Pointer,Mask3DType>(maskPointer,numberOfRows);
            // creazione clusterid
            int* clusterid = new int[numberOfRows];
            algorithmToExecute->execute(transponse,mask,numberOfRows,numberOfColumns,clusterid,getNClusters(),getAlgorithmParameters());
            // creazione immagine di output
            ClusteringImage3DType::Pointer output = ClusteringImage3DType::New();
            ClusteringImage3DType::IndexType startIndex;
            startIndex.Fill(0);
            ClusteringImage3DType::SizeType regionSize;
            regionSize[0] = video->GetLargestPossibleRegion().GetSize()[0];
            regionSize[1] = video->GetLargestPossibleRegion().GetSize()[1];
            regionSize[2] = video->GetLargestPossibleRegion().GetSize()[2];
            ClusteringImage3DType::RegionType region(startIndex,regionSize);
            output->SetRegions(region);
            output->Allocate();
            createClusteringImage<ClusteringImage3DType::Pointer,ClusteringImage3DType>(output,clusterid,mask);
            // delete dei dati sullo heap
            delete[] mask;
            delete[] clusterid;
            // scrivi l'immagine
            QString fileName = QUrl::fromLocalFile(subject->getName() + "_" + algorithmToExecute->getName()).path();
            videoHandler->writeImage<ClusteringImage3DType::Pointer,ClusteringImage3DType>(output,fileName,path,outputFormat);
            emit algorithmExecuted(path + fileName + outputFormat);
        }
        // delete dei dati
        for(int i=0;i<numberOfRows;i++)
            delete[] transponse[i];
        delete[] transponse;
    }

}

void DynamicProtocol::execute(romeo::model::datasets::AbstractSubject *subject,QString path,bool saveFeatures,QString outputFormat)
{
    setStopAnalysis(false);
    InputFormat dimensions = subject->getType();
    if(dimensions == TYPE2DT)
        video2DExecute(subject,path,saveFeatures,outputFormat);
    else
        video3DExecute(subject,path,saveFeatures,outputFormat);
}

ProtocolType DynamicProtocol::getType(){
    return DYNAMIC;
}

int DynamicProtocol::getWindowSize() const
{
    return 3;
}

int DynamicProtocol::getDistanceToGlcm() const
{
    return 1;
}

int DynamicProtocol::getFrameInit() const {
    return frameInit;
}

int DynamicProtocol::getFrameEnd() const {
    return frameEnd;
}
