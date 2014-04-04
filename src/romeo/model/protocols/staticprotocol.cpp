/**
* \file staticprotocol.cpp
* \author Matteo Pozza
* \date 2014-02-07
**
* \brief Header della classe StaticProtocol del package romeo::model::protocols
*/

#include "staticprotocol.h"
#include <QThread>

using namespace romeo::model::protocols;
using namespace romeo::model::imageIO;
using namespace romeo::model;

StaticProtocol::StaticProtocol(QString nomeP, QString desc, algorithms::AbstractAlgorithm* alg, int clusterNum, QList<QString> algParameters, QList<features::AbstractFeature*> feat, bool testProtocol, int window, int distance):
    AbstractProtocol(nomeP,desc,alg, clusterNum, algParameters, feat,testProtocol), windowSize(window), distanceToGLCM(distance)
{
}

double** StaticProtocol::read2DImage(Image2DType::Pointer input) {
    double** result = new double*[3];
    for(int i=0;i<3;i++)
        result[i] = new double[input->GetLargestPossibleRegion().GetNumberOfPixels()];
    itk::ImageRegionIterator<Image2DType> inputIterator(input , input->GetLargestPossibleRegion());
    int index=0;
    while(!inputIterator.IsAtEnd()) {
        result[0][index] = static_cast<double>(inputIterator.Get()[0]);
        result[1][index] = static_cast<double>(inputIterator.Get()[1]);
        result[2][index] = static_cast<double>(inputIterator.Get()[2]);
        ++index;
        ++inputIterator;
    }
    return result;
}

double** StaticProtocol::read3DImage(Image3DType::Pointer input) {
    double** result = new double*;
    result[0] = new double[input->GetLargestPossibleRegion().GetNumberOfPixels()];
    itk::ImageRegionIterator<Image3DType> inputIterator(input , input->GetLargestPossibleRegion());
    int index=0;
    while(!inputIterator.IsAtEnd()) {
        result[0][index] = static_cast<double>(inputIterator.Get());
        ++index;
        ++inputIterator;
    }
    return result;
}

double** StaticProtocol::applyFirstOrderFeature2D(Image2DType::Pointer input,Image2DType::Pointer output,Mask2DType::Pointer mask,romeo::model::protocols::features::FirstOrderFeature* feature) {

    // input è l'immagine in ingresso
    // output è l'immagine in uscita
    // mask è la maschera
    // feature è la feature da eseguire

    typedef double (*MyPrototype)(double* data,int size,int dimension);
    MyPrototype featureExtractor = (MyPrototype) QLibrary::resolve(feature->getDynamicLibraryPath(),feature->getDynamicFunctionName().toStdString().c_str());
    if(!featureExtractor){
        // non viene trovata le libreria
        QString message = "Cannot find library " + feature->getDynamicFunctionName() + " located in " + feature->getDynamicLibraryPath();
        throw message;
    }
    int dimension = 2;
    // imposta raggio della finestra scorrevole: raggio = 1 -> finestra = 3
    Image2DType::SizeType radius;
    radius.Fill(windowSize/2);
    Image2DType::Pointer mirror = createMirror<Image2DType::Pointer,Image2DType>(input,windowSize/2);
    Image2DType::RegionType outputRegion = getRegion<Image2DType::Pointer,Image2DType>(input);

    // iteratore per l'immagine in input
    itk::NeighborhoodIterator<Image2DType> inputIterator(radius, mirror , outputRegion);
    inputIterator.NeedToUseBoundaryConditionOff();
    // iteratore per l'immagine in output
    itk::ImageRegionIterator<Image2DType> outputIterator(output , output->GetLargestPossibleRegion());

    // numero di pixel
    const int length = input->GetLargestPossibleRegion().GetNumberOfPixels();

    // iteratore per la maschera
    itk::ImageRegionIterator<Mask2DType> maskIterator;
    // maschera in un array: servirà per createImage
    int* maskArray;
    if(mask.IsNotNull()) {
        maskIterator = itk::ImageRegionIterator<Mask2DType>(mask , mask->GetLargestPossibleRegion());
        maskArray = getMask<Mask2DType::Pointer,Mask2DType>(mask,length);
    }
    else {
        maskArray = new int[length];
        for(int i=0;i<length;i++)
            maskArray[i] = 255;
    }

    // allocazione degli array di double da restituire per l'eventuale algoritmo di clustering
    double** result = new double*[3];
    for(int i=0;i<3;i++)
        result[i] = new double[length];

    if(mask.IsNotNull()) {
        // considero la presenza della mask
        int index =0;
        while(!inputIterator.IsAtEnd()) {
            if(static_cast<int>(maskIterator.Get())!=0) {
                // pow(size,dimension) è il numero di elementi dentro la finestra scorrevole
                // per ciascun colore creo tre array differenti
                double redArray[static_cast<int>(pow(windowSize,dimension))];
                double greenArray[static_cast<int>(pow(windowSize,dimension))];
                double blueArray[static_cast<int>(pow(windowSize,dimension))];
                // riempimento degli array
                for(int i=0;i<static_cast<int>(pow(windowSize,dimension));i++) {
                    redArray[i]=inputIterator.GetPixel(i)[0];
                    greenArray[i]=inputIterator.GetPixel(i)[1];
                    blueArray[i]=inputIterator.GetPixel(i)[2];
                }
                // applicazione feature
                double redValue = featureExtractor(redArray,windowSize,dimension);
                double greenValue = featureExtractor(greenArray,windowSize,dimension);
                double blueValue = featureExtractor(blueArray,windowSize,dimension);
                // imposto i valori degli array di double
                result[0][index]=redValue;
                result[1][index]=greenValue;
                result[2][index]=blueValue;
            }
            else {
                result[0][index]=0.0;
                result[1][index]=0.0;
                result[2][index]=0.0;
            }
            ++inputIterator;
            ++maskIterator;
            ++index;
        }
    }
    else {
        // ignoro la mask
        int index =0;
        while(!inputIterator.IsAtEnd()) {
            // pow(size,dimension) è il numero di elementi dentro la finestra scorrevole
            // per ciascun colore creo tre array differenti
            double redArray[static_cast<int>(pow(windowSize,dimension))];
            double greenArray[static_cast<int>(pow(windowSize,dimension))];
            double blueArray[static_cast<int>(pow(windowSize,dimension))];
            // riempimento degli array
            for(int i=0;i<static_cast<int>(pow(windowSize,dimension));i++) {
                redArray[i]=inputIterator.GetPixel(i)[0];
                greenArray[i]=inputIterator.GetPixel(i)[1];
                blueArray[i]=inputIterator.GetPixel(i)[2];
            }
            // applicazione feature
            double redValue = featureExtractor(redArray,windowSize,dimension);
            double greenValue = featureExtractor(greenArray,windowSize,dimension);
            double blueValue = featureExtractor(blueArray,windowSize,dimension);
            // imposto i valori degli array di double
            result[0][index]=redValue;
            result[1][index]=greenValue;
            result[2][index]=blueValue;
            ++inputIterator;
            ++index;
        }
    }
    // creazione immagine output
    createImage2D(outputIterator,result,maskArray,length);
    // cancellazione della maschera
    delete[] maskArray;
    // ritorna gli array di double per l'algoritmo di clustering
    return result;
}

double* StaticProtocol::applyFirstOrderFeature3D(Image3DType::Pointer input,Image3DType::Pointer output,Mask3DType::Pointer mask,romeo::model::protocols::features::FirstOrderFeature* feature) {

    // input è l'immagine in ingresso
    // output è l'immagine in uscita
    // mask è la maschera
    // feature è la feature da eseguire

    typedef double (*MyPrototype)(double* data,int size,int dimension);
    MyPrototype featureExtractor = (MyPrototype) QLibrary::resolve(feature->getDynamicLibraryPath(),feature->getDynamicFunctionName().toStdString().c_str());
    if(!featureExtractor){
        // non viene trovata le libreria
        QString message = "Cannot find library " + feature->getDynamicFunctionName() + " located in " + feature->getDynamicLibraryPath();
        throw message;
    }
    int dimension = 3;
    // imposta raggio della finestra scorrevole: raggio = 1 -> finestra = 3
    Image3DType::SizeType radius;
    radius.Fill(windowSize/2);
    Image3DType::Pointer mirror = createMirror<Image3DType::Pointer,Image3DType>(input,windowSize/2);
    Image3DType::RegionType outputRegion = getRegion<Image3DType::Pointer,Image3DType>(input);

    // iteratore per l'immagine in input
    itk::NeighborhoodIterator<Image3DType> inputIterator(radius, mirror , outputRegion);
    inputIterator.NeedToUseBoundaryConditionOff();
    // iteratore per l'immagine in output
    itk::ImageRegionIterator<Image3DType> outputIterator(output , output->GetLargestPossibleRegion());

    // numero di pixel
    const int length = input->GetLargestPossibleRegion().GetNumberOfPixels();

    // iteratore per la maschera
    itk::ImageRegionIterator<Mask3DType> maskIterator;
    // maschera in un array: servirà per createImage
    int* maskArray;
    if(mask.IsNotNull()) {
        maskIterator = itk::ImageRegionIterator<Mask3DType>(mask , mask->GetLargestPossibleRegion());
        maskArray = getMask<Mask3DType::Pointer,Mask3DType>(mask,length);
    }
    else {
        maskArray = new int[length];
        for(int i=0;i<length;i++)
            maskArray[i] = 255;
    }

    // allocazione degli array di double da restituire per l'eventuale algoritmo di clustering
    double* result = new double[length];

    if(mask.IsNotNull()) {
        // considero la presenza della mask
        int index =0;
        while(!inputIterator.IsAtEnd()) {
            if(static_cast<int>(maskIterator.Get())!=0) {
                // pow(size,dimension) è il numero di elementi dentro la finestra scorrevole
                // per ciascun colore creo tre array differenti
                double valueArray[static_cast<int>(pow(windowSize,dimension))];
                // riempimento degli array
                for(int i=0;i<static_cast<int>(pow(windowSize,dimension));i++)
                    valueArray[i]=static_cast<double>(inputIterator.GetPixel(i));
                // applicazione feature
                double value = featureExtractor(valueArray,windowSize,dimension);
                // imposto i valori degli array di double
                result[index]=value;
            }
            else
                result[index]=0.0;
            ++inputIterator;
            ++maskIterator;
            ++index;
        }
    }
    else {
        // ignoro la mask
        int index =0;
        while(!inputIterator.IsAtEnd()) {
            // pow(size,dimension) è il numero di elementi dentro la finestra scorrevole
            // per ciascun colore creo tre array differenti
            double valueArray[static_cast<int>(pow(windowSize,dimension))];
            // riempimento degli array
            for(int i=0;i<static_cast<int>(pow(windowSize,dimension));i++)
                valueArray[i]=static_cast<double>(inputIterator.GetPixel(i));
            // applicazione feature
            double value = featureExtractor(valueArray,windowSize,dimension);
            // imposto i valori degli array di double
            result[index]=value;
            ++inputIterator;
            ++index;
        }
    }
    // creazione immagine output
    createImage3D(outputIterator,result,maskArray,length);
    // cancellazione della maschera
    delete[] maskArray;
    // ritorna gli array di double per l'algoritmo di clustering
    return result;
}

double** StaticProtocol::applySecondOrderFeature2D(Image2DType::Pointer input,Image2DType::Pointer output,Mask2DType::Pointer mask,int distance,romeo::model::protocols::features::SecondOrderFeature* feature) {

    // input è l'immagine in ingresso
    // output è l'immagine in uscita
    // mask è la maschera
    // distance è la distanza dalla GLCM

    typedef double (*MyPrototype)(int data[4][4]);
    MyPrototype featureExtractor = (MyPrototype) QLibrary::resolve(feature->getDynamicLibraryPath(),feature->getDynamicFunctionName().toStdString().c_str());

    int dimension = 2;
    // imposta raggio della finestra scorrevole: raggio = 1 -> finestra = 3
    Image2DType::SizeType radius;
    radius.Fill(windowSize/2);

    Image2DType::Pointer mirror = createMirror<Image2DType::Pointer,Image2DType>(input,windowSize/2);
    Image2DType::RegionType outputRegion = getRegion<Image2DType::Pointer,Image2DType>(input);

    // iteratore per l'immagine in input
    itk::NeighborhoodIterator<Image2DType> inputIterator(radius, mirror , outputRegion);
    inputIterator.NeedToUseBoundaryConditionOff();
    // iteratore per l'immagine in output
    itk::ImageRegionIterator<Image2DType> outputIterator(output , output->GetLargestPossibleRegion());

    // numero di pixel
    const int length = input->GetLargestPossibleRegion().GetNumberOfPixels();

    // iteratore per la maschera
    itk::ImageRegionIterator<Mask2DType> maskIterator;
    // maschera in un array: servirà per createImage
    int* maskArray;
    if(mask.IsNotNull()) {
        maskIterator = itk::ImageRegionIterator<Mask2DType>(mask , mask->GetLargestPossibleRegion());
        maskArray = getMask<Mask2DType::Pointer,Mask2DType>(mask,length);
    }
    else {
        maskArray = new int[length];
        for(int i=0;i<length;i++)
            maskArray[i] = 255;
    }


    // allocazione dell'array di double da restituire per l'eventuale algoritmo di clustering
    double** result = new double*[3];
    for(int i=0;i<3;i++)
        result[i] = new double[length];

    if(mask.IsNotNull()) {
        // considero la presenza della mask
        int index =0;
        while(!inputIterator.IsAtEnd()) {
            if(static_cast<int>(maskIterator.Get())!=0) {
                for(int color=0;color<3;color++) {
                    // definisco una regione
                    Mask2DType::IndexType regionIndex;
                    regionIndex.Fill(0);
                    Mask2DType::SizeType regionSize;
                    regionSize.Fill(windowSize);
                    Mask2DType::RegionType region(regionIndex,regionSize);
                    // istanzio una nuova immagine
                    Mask2DType::Pointer neighbor = Mask2DType::New();
                    neighbor->SetRegions(region);
                    neighbor->Allocate();
                    // la riempio con i valori dell'iteratore
                    itk::ImageRegionIterator<Mask2DType> pieceIterator(neighbor , neighbor->GetLargestPossibleRegion());
                    for(int i=0;i<static_cast<int>(pow(windowSize,dimension));i++) {
                        pieceIterator.Set(inputIterator.GetPixel(i)[color]);
                        ++pieceIterator;
                    }
                    // procuro la GLCM
                    int data[4][4];
                    getGLCM<Mask2DType,Mask2DType::Pointer>(neighbor,data,distance);
                    // diamo l'array in pasto alla feature di secondo ordine
                    double value = featureExtractor(data);
                    result[color][index] = value;
                }
            }
            else {
                result[0][index] = 0.0;
                result[1][index] = 0.0;
                result[2][index] = 0.0;
            }
            ++inputIterator;
            ++maskIterator;
            ++index;
        }
    }
    else {
        // ignoro la mask
        int index =0;
        while(!inputIterator.IsAtEnd()) {
            for(int color=0;color<3;color++) {
                // definisco una regione
                // il tipo è quello della maschera dal momento che devo raccogliere un solo colore
                Mask2DType::IndexType regionIndex;
                regionIndex.Fill(0);
                Mask2DType::SizeType regionSize;
                regionSize.Fill(windowSize);
                Mask2DType::RegionType region(regionIndex,regionSize);
                // istanzio una nuova immagine
                Mask2DType::Pointer neighbor = Mask2DType::New();
                neighbor->SetRegions(region);
                neighbor->Allocate();
                // la riempio con i valori dell'iteratore
                itk::ImageRegionIterator<Mask2DType> pieceIterator(neighbor , neighbor->GetLargestPossibleRegion());
                for(int i=0;i<static_cast<int>(pow(windowSize,dimension));i++) {
                    pieceIterator.Set(inputIterator.GetPixel(i)[color]);
                    ++pieceIterator;
                }
                // procuro la GLCM
                int data[4][4];
                getGLCM<Mask2DType,Mask2DType::Pointer>(neighbor,data,distance);
                // diamo l'array in pasto alla feature di secondo ordine
                double value = featureExtractor(data);
                result[color][index] = value;
            }
            ++inputIterator;
            ++index;
        }
    }
    // creazione immagine output
    createImage2D(outputIterator,result,maskArray,length);
    // cancellazione della maschera
    delete[] maskArray;
    // ritorna gli array di double per l'algoritmo di clustering
    return result;
}

double* StaticProtocol::applySecondOrderFeature3D(Image3DType::Pointer input,Image3DType::Pointer output,Mask3DType::Pointer mask,int distance,romeo::model::protocols::features::SecondOrderFeature* feature) {

    // input è l'immagine in ingresso
    // output è l'immagine in uscita
    // mask è la maschera
    // distance è la distanza dalla GLCM

    typedef double (*MyPrototype)(int data[4][4]);
    MyPrototype featureExtractor = (MyPrototype) QLibrary::resolve(feature->getDynamicLibraryPath(),feature->getDynamicFunctionName().toStdString().c_str());

    int dimension = 3;
    // imposta raggio della finestra scorrevole: raggio = 1 -> finestra = 3
    Image3DType::SizeType radius;
    radius.Fill(windowSize/2);

    Image3DType::Pointer mirror = createMirror<Image3DType::Pointer,Image3DType>(input,windowSize/2);
    Image3DType::RegionType outputRegion = getRegion<Image3DType::Pointer,Image3DType>(input);

    // iteratore per l'immagine in input
    itk::NeighborhoodIterator<Image3DType> inputIterator(radius, mirror , outputRegion);
    inputIterator.NeedToUseBoundaryConditionOff();
    // iteratore per l'immagine in output
    itk::ImageRegionIterator<Image3DType> outputIterator(output , output->GetLargestPossibleRegion());

    // numero di pixel
    const int length = input->GetLargestPossibleRegion().GetNumberOfPixels();

    // iteratore per la maschera
    itk::ImageRegionIterator<Mask3DType> maskIterator;
    // maschera in un array: servirà per createImage
    int* maskArray;
    if(mask.IsNotNull()) {
        maskIterator = itk::ImageRegionIterator<Mask3DType>(mask , mask->GetLargestPossibleRegion());
        maskArray = getMask<Mask3DType::Pointer,Mask3DType>(mask,length);
    }
    else {
        maskArray = new int[length];
        for(int i=0;i<length;i++)
            maskArray[i] = 255;
    }


    // allocazione dell'array di double da restituire per l'eventuale algoritmo di clustering
    double* result = new double[length];

    if(mask.IsNotNull()) {
        // considero la presenza della mask
        int index =0;
        while(!inputIterator.IsAtEnd()) {
            if(static_cast<int>(maskIterator.Get())!=0) {
                // definisco una regione
                Image3DType::IndexType regionIndex;
                regionIndex.Fill(0);
                Image3DType::SizeType regionSize;
                regionSize.Fill(windowSize);
                Image3DType::RegionType region(regionIndex,regionSize);
                // istanzio una nuova immagine
                Image3DType::Pointer neighbor = Image3DType::New();
                neighbor->SetRegions(region);
                neighbor->Allocate();
                // la riempio con i valori dell'iteratore
                itk::ImageRegionIterator<Image3DType> pieceIterator(neighbor , neighbor->GetLargestPossibleRegion());
                for(int i=0;i<static_cast<int>(pow(windowSize,dimension));i++) {
                    pieceIterator.Set(inputIterator.GetPixel(i));
                    ++pieceIterator;
                }
                // procuro la GLCM
                int data[4][4];
                getGLCM<Image3DType,Image3DType::Pointer>(neighbor,data,distance);
                // diamo l'array in pasto alla feature di secondo ordine
                double value = featureExtractor(data);
                result[index] = value;
            }
            else
                result[index] = 0.0;
            ++inputIterator;
            ++maskIterator;
            ++index;
        }
    }
    else {
        // ignoro la mask
        int index =0;
        while(!inputIterator.IsAtEnd()) {
            // definisco una regione
            Image3DType::IndexType regionIndex;
            regionIndex.Fill(0);
            Image3DType::SizeType regionSize;
            regionSize.Fill(windowSize);
            Image3DType::RegionType region(regionIndex,regionSize);
            // istanzio una nuova immagine
            Image3DType::Pointer neighbor = Image3DType::New();
            neighbor->SetRegions(region);
            neighbor->Allocate();
            // la riempio con i valori dell'iteratore
            itk::ImageRegionIterator<Image3DType> pieceIterator(neighbor , neighbor->GetLargestPossibleRegion());
            for(int i=0;i<static_cast<int>(pow(windowSize,dimension));i++) {
                pieceIterator.Set(inputIterator.GetPixel(i));
                ++pieceIterator;
            }
            // procuro la GLCM
            int data[4][4];
            getGLCM<Image3DType,Image3DType::Pointer>(neighbor,data,distance);
            // diamo l'array in pasto alla feature di secondo ordine
            double value = featureExtractor(data);
            result[index] = value;
            ++inputIterator;
            ++index;
        }
    }
    // creazione immagine output
    createImage3D(outputIterator,result,maskArray,length);
    // cancellazione della maschera
    delete[] maskArray;
    // ritorna gli array di double per l'algoritmo di clustering
    return result;
}

void StaticProtocol::image2DExecute(romeo::model::datasets::AbstractSubject *subject,QString path,bool saveFeatures,QString outputFormat) {
    // il path viene aggiustato rispetto ai corretti separatori in base al sistema operativo
    path = QDir::toNativeSeparators(path + "/");
    if(outputFormat== "INPUT")
        outputFormat = QString(".") + subject->getSubject().split(".").takeLast();
    romeo::model::imageIO::HandlerIOStatic* imageHandler = romeo::model::imageIO::HandlerIOStatic::getInstance();
    Image2DType::Pointer imagePointer = imageHandler->readImage<Image2DType::Pointer,Image2DType>(subject->getSubject());
    Mask2DType::Pointer maskPointer = imageHandler->readImage<Mask2DType::Pointer,Mask2DType>(subject->getMask());
    QList<romeo::model::protocols::features::AbstractFeature*> featureList = getFeatures();
    int numberOfRows,numberOfColumns;
    double** result;
    if(featureList.size()>0) {
        // ci sono features da estrarre
        numberOfRows = imagePointer->GetLargestPossibleRegion().GetNumberOfPixels();
        numberOfColumns = 3*featureList.size();
        int requestedMemory = numberOfRows*numberOfColumns;
        // se la memoria richiesta è eccessiva lancia una eccezione
        checkRequestedMemory(requestedMemory);
        result = new double*[numberOfColumns];
        int index = 0;
        for(int i=0;i<featureList.size() && !getStopAnalysis();i++) {

            Image2DType::Pointer outputFeature = Image2DType::New();
            outputFeature->SetRegions(imagePointer->GetLargestPossibleRegion());
            outputFeature->Allocate();
            romeo::model::protocols::features::AbstractFeature* currentFeature = featureList[i];
            double** singleFeature;
            romeo::model::protocols::features::FirstOrderFeature* firstOrderFeature = dynamic_cast<romeo::model::protocols::features::FirstOrderFeature*>(featureList[i]);
            if(firstOrderFeature) {
                singleFeature = applyFirstOrderFeature2D(imagePointer,outputFeature,maskPointer,firstOrderFeature);
            }
            else {
                romeo::model::protocols::features::SecondOrderFeature* secondOrderFeature = dynamic_cast<romeo::model::protocols::features::SecondOrderFeature*>(featureList[i]);
                if(secondOrderFeature)
                    singleFeature = applySecondOrderFeature2D(imagePointer,outputFeature,maskPointer,distanceToGLCM,secondOrderFeature);
            }
            // singleFeature è una matrice [ncols][nrows]
            for(int j=0;j<3;j++) {
                result[index]=singleFeature[j];
                ++index;
            }
            if(saveFeatures) {
                QString fileName = QUrl::fromLocalFile(subject->getName() + "_" + currentFeature->getName()).path();
                imageHandler->writeImage<Image2DType::Pointer,Image2DType>(outputFeature,fileName,path,outputFormat);
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
        numberOfRows = imagePointer->GetLargestPossibleRegion().GetNumberOfPixels();
        numberOfColumns = 3;
        int requestedMemory = numberOfRows*numberOfColumns;
        // se la memoria richiesta è eccessiva lancia una eccezione
        checkRequestedMemory(requestedMemory);
        result = read2DImage(imagePointer);
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
            Image2DType::Pointer output = Image2DType::New();
            output->SetRegions(imagePointer->GetLargestPossibleRegion());
            output->Allocate();
            createClusteringImage<Image2DType::Pointer,Image2DType>(output,clusterid,mask);
            // delete dei dati sullo heap
            delete[] mask;
            delete[] clusterid;
            // scrivi l'immagine
            QString fileName = QUrl::fromLocalFile(subject->getName() + "_" + algorithmToExecute->getName()).path();
            imageHandler->writeImage<Image2DType::Pointer,Image2DType>(output,fileName,path,outputFormat);
            emit algorithmExecuted(path + fileName + outputFormat);
        }
        // delete dei dati
        for(int i=0;i<numberOfRows;i++)
            delete[] transponse[i];
        delete[] transponse;
    }

}

void StaticProtocol::image3DExecute(romeo::model::datasets::AbstractSubject *subject,QString path,bool saveFeatures,QString outputFormat) {
    // il path viene aggiustato rispetto ai corretti separatori in base al sistema operativo
    path = QDir::toNativeSeparators(path + "/");
    if(outputFormat== "INPUT")
        outputFormat = QString(".") + subject->getSubject().split(".").takeLast();
    romeo::model::imageIO::HandlerIOStatic* imageHandler = romeo::model::imageIO::HandlerIOStatic::getInstance();
    typename Image3DType::Pointer imagePointer = imageHandler->readImage<Image3DType::Pointer,Image3DType>(subject->getSubject());
    typename Mask3DType::Pointer maskPointer = imageHandler->readImage<Mask3DType::Pointer,Mask3DType>(subject->getMask());
    QList<romeo::model::protocols::features::AbstractFeature*> featureList = getFeatures();
    int numberOfRows,numberOfColumns;
    double** result;
    if(featureList.size()>0) {
        // ci sono features da estrarre
        numberOfRows = imagePointer->GetLargestPossibleRegion().GetNumberOfPixels();
        numberOfColumns = featureList.size();
        int requestedMemory = numberOfRows*numberOfColumns;
        // se la memoria richiesta è eccessiva lancia una eccezione
        checkRequestedMemory(requestedMemory);
        result = new double*[numberOfColumns];
        int index = 0;
        for(int i=0;i<featureList.size() && !getStopAnalysis();i++) {

            Image3DType::Pointer outputFeature = Image3DType::New();
            outputFeature->SetRegions(imagePointer->GetLargestPossibleRegion());
            outputFeature->Allocate();
            romeo::model::protocols::features::AbstractFeature* currentFeature = featureList[i];
            double* singleFeature;
            romeo::model::protocols::features::FirstOrderFeature* firstOrderFeature = dynamic_cast<romeo::model::protocols::features::FirstOrderFeature*>(featureList[i]);
            if(firstOrderFeature) {
                singleFeature = applyFirstOrderFeature3D(imagePointer,outputFeature,maskPointer,firstOrderFeature);
            }
            else {
                romeo::model::protocols::features::SecondOrderFeature* secondOrderFeature = dynamic_cast<romeo::model::protocols::features::SecondOrderFeature*>(featureList[i]);
                if(secondOrderFeature)
                    singleFeature = applySecondOrderFeature3D(imagePointer,outputFeature,maskPointer,distanceToGLCM,secondOrderFeature);
            }
            // singleFeature è una matrice [ncols][nrows]
            result[index]=singleFeature;
            ++index;
            if(saveFeatures) {
                QString fileName = QUrl::fromLocalFile(subject->getName() + "_" + currentFeature->getName()).path();
                imageHandler->writeImage<Image3DType::Pointer,Image3DType>(outputFeature,fileName,path,outputFormat);
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
        numberOfRows = imagePointer->GetLargestPossibleRegion().GetNumberOfPixels();
        numberOfColumns = 1;
        int requestedMemory = numberOfRows*numberOfColumns;
        // se la memoria richiesta è eccessiva lancia una eccezione
        checkRequestedMemory(requestedMemory);
        result = read3DImage(imagePointer);
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
            output->SetRegions(imagePointer->GetLargestPossibleRegion());
            output->Allocate();
            createClusteringImage<ClusteringImage3DType::Pointer,ClusteringImage3DType>(output,clusterid,mask);
            // delete dei dati sullo heap
            delete[] mask;
            delete[] clusterid;
            // scrivi l'immagine
            QString fileName = QUrl::fromLocalFile(subject->getName() + "_" + algorithmToExecute->getName()).path();
            imageHandler->writeImage<ClusteringImage3DType::Pointer,ClusteringImage3DType>(output,fileName,path,outputFormat);
            emit algorithmExecuted(path + fileName + outputFormat);
        }
        // delete dei dati
        for(int i=0;i<numberOfRows;i++)
            delete[] transponse[i];
        delete[] transponse;
    }
}

void StaticProtocol::execute(romeo::model::datasets::AbstractSubject *subject,QString path,bool saveFeatures,QString outputFormat)
{
    setStopAnalysis(false);
    InputFormat dimensions = subject->getType();
    if(dimensions == TYPE2D)
        image2DExecute(subject,path,saveFeatures,outputFormat);
    else
        image3DExecute(subject,path,saveFeatures,outputFormat);
}

ProtocolType StaticProtocol::getType(){
    return STATIC;
}
int StaticProtocol::getWindowSize() const
{
    return windowSize;
}

void StaticProtocol::setWindowSize(int value)
{
    windowSize = value;
}

int StaticProtocol::getDistanceToGlcm() const
{
    return distanceToGLCM;
}

void StaticProtocol::setDistanceToGlcm(int value)
{
    distanceToGLCM = value;
}

int StaticProtocol::getFrameInit() const {
    return -1;
}

int StaticProtocol::getFrameEnd() const {
    return -1;
}
