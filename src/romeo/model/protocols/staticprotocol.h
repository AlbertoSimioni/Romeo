/**
* \file staticprotocol.h
* \author Matteo Pozza
* \date 2014-02-07
**
* \brief Header della classe StaticProtocol del package romeo::model::protocols
*/

#ifndef STATICPROTOCOL_H
#define STATICPROTOCOL_H
#include "abstractprotocol.h"
// QT
#include <QLibrary>
#include <QList>
#include <QDir>
#include <QDebug>
#include <QUrl>
// ITK
#include "itkImage.h"
#include "itkRGBPixel.h"
#include "itkNeighborhoodIterator.h"
#include "itkMirrorPadImageFilter.h"
#include "itkScalarImageToCooccurrenceMatrixFilter.h"
//
#include <src/romeo/model/inputformats.h>
#include <src/romeo/model/imageIO/handleriostatic.h>
#include <src/romeo/model/protocols/features/firstorderfeature.h>
#include <src/romeo/model/protocols/features/secondorderfeature.h>
#include <src/romeo/model/protocols/features/abstractfeature.h>
#include <src/romeo/model/protocols/algorithms/abstractalgorithm.h>
#include <src/romeo/model/protocols/color.h>

namespace romeo {
namespace model {
namespace protocols{

/*!
 * \brief La classe StaticProtocol rappresenta i protocolli che eseguono su immagini statiche.
 * *
 * La classe eredita da AbstractProtocol e implementa il metodo virtuale puro execute(AbstractSubject*) con cui esegue un protocollo sul subject, che deve essere un immagine di tipo statico.
 */
class StaticProtocol : public AbstractProtocol
{



public:
    /*!
     * \brief Costruisce un nuovo protocollo di tipo statico con l''algoritmo e le features indicate.
     * \param nomeP Nome del protocollo da costruire.
     * \param desc La descrizione del protocollo sotto forma di stringa.
     * \param alg Un puntatore all'algoritmo di clustering che il protocollo deve eseguire.
     * \param clusterNum Parametro che indica il numero di cluster che deve generare l'algoritmo.
     * \param parameters Lista dei valori dei parametri dell'algoritmo associato al protocollo.
     * \param feat Un vettore di puntatori a features che fanno parte del protocollo.
     * \param testProtocol Valore booleano che indica se il protocollo è di test.
     * \param window Valore della finestra di elaborazione.
     * \param distance Valore della distanceToGLCM voluta.
     */
    StaticProtocol(QString nomeP, QString desc, algorithms::AbstractAlgorithm* alg, int clusterNum, QList<QString> algParameters, QList<features::AbstractFeature*> feat, bool testProtocol, int window=3, int distance=1);
    /*!
     * \brief Override del metodo execute della classe astratta AbstractProtocol
     * \param Il soggetto utilizzato per eseguire l'analisi, deve contenere un immagine di tipo statico
     */
    virtual void execute(datasets::AbstractSubject *subject,QString path,bool saveFeatures,QString outputFormat);
    /*!
     * \brief Funzione virtuale che ritorna il tipo del protocollo corrente, per la classe StaticProtocol ritornerà ProtocolType::STATIC. La funzione è override di quella definita nella superclasse e può essere chiamata avendo solo un riferimento a AbstractProtocol.
     */
    virtual ProtocolType getType();
    /*!
     * \brief Ritorna la dimensione della finestra su cui vengono eseguite le operazioni.
     */
    virtual int getWindowSize() const;
    /*!
     * \brief Ritorna un intero che indica la dimensione della GLCM(Gray Level Concurrency Matrix).
     */
    virtual int getDistanceToGlcm() const;
    /*!
     * \brief Imposta ia valore della matrice GLCM a value.
     */
    void setDistanceToGlcm(int value);
    /*!
     * \brief Imposta la dimensione della finestra su cui eseguiere le operazioni a value.
     */
    void setWindowSize(int value);
    /*!
     *
     */
    static int roundToInt(double num);
    /*!
     *
     */
    static int* normalize(double* array,int length);
    /*!
     *
     */
    static double** transform(double** result,const int nrows,const int ncolumns);
    /*!
     *
     */
    template<typename PointerType,typename ImageType>
    double** readImage(PointerType input) {
        // legge l'immagine e torna una matrice [ncols][nrows]
        double** result = new double*[3];
        for(int i=0;i<3;i++)
            result[i] = new double[input->GetLargestPossibleRegion().GetNumberOfPixels()];
        itk::ImageRegionIterator<ImageType> inputIterator(input , input->GetLargestPossibleRegion());
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
    /*!
     *
     */
    template<typename ImageType>
    void createImage(itk::ImageRegionIterator<ImageType> outputIterator,double** result,int length) {
        // metodo per creare l'immagine in output
        // outputIterator è l'itertaore dell'immagine in output
        // result è la matrice di double relativa al risultato
        // length è in numero di pixel dell'immagine
        int* redValues = normalize(result[0],length);
        int* greenValues = normalize(result[1],length);
        int* blueValues = normalize(result[2],length);
        int index = 0;
        while(!outputIterator.IsAtEnd()) {
            typename ImageType::PixelType outputPixel;
            outputPixel.Set(redValues[index],greenValues[index],blueValues[index]);
            // scrivo il pixel nell'immagine in output
            outputIterator.Set(outputPixel);
            ++index;
            ++outputIterator;
        }
        delete[] redValues;
        delete[] greenValues;
        delete[] blueValues;
    }
    /*!
     *
     */
    template<typename MaskPointer,typename MaskType>
    int* getMask(MaskPointer mask,const int nrows) {

        int* maskArray = new int[nrows];
        for(int i=0;i<nrows;i++)
            maskArray[i]=1;

        itk::ImageRegionIterator<MaskType> maskIterator;
        if(mask.IsNotNull()) {
            maskIterator = itk::ImageRegionIterator<MaskType>(mask , mask->GetLargestPossibleRegion());
            int i=0;
            while(!maskIterator.IsAtEnd()) {
                maskArray[i]=static_cast<int>(maskIterator.Get());
                ++i;
                ++maskIterator;
            }
        }

        return maskArray;
    }
    /*!
     * \brief createClusteringImage
     */
    template<typename ImagePointer,typename ImageType,typename PixelType>
    void createClusteringImage(ImagePointer output,int* clusterid,int* maskArray) {
        itk::ImageRegionIterator<ImageType> iterator(output , output->GetLargestPossibleRegion());
        int index = 0;
        while(!iterator.IsAtEnd()) {
            PixelType pixel;
            int cluster = clusterid[index];
            int maskValue = maskArray[index];
            if(maskValue==0)
                pixel.Set(0,0,0);
            else {
                int* color = Color::getColor(cluster);
                pixel.Set(color[0],color[1],color[2]);
            }
            iterator.Set(pixel);
            ++index;
            ++iterator;
        }
    }
    /*!
     *
     */
    template<typename ImagePointer,typename ImageType>
    ImagePointer createMirror(ImagePointer input,int pad) {
        // funzione per la creazione di una immagine con pad di pixel a specchio
        // input è l'immagine in input
        // pad è il numero di pixel di cui si vuole fare il pad (generalmente metà della taglia della finestra scorrevole)
        typename itk::MirrorPadImageFilter<ImageType,ImageType>::Pointer mirror;
        mirror = itk::MirrorPadImageFilter<ImageType,ImageType>::New();
        mirror->SetInput(input);
        typename ImageType::SizeType radius;
        radius.Fill(pad);
        mirror->SetPadLowerBound(radius);
        mirror->SetPadUpperBound(radius);
        mirror->Update();
        return mirror->GetOutput();
    }
    /*!
     *
     */
    template<typename ImagePointer,typename ImageType>
    typename ImageType::RegionType getRegion(ImagePointer input) {
        // restituisce la regione di interesse relativa all'immagine con pad a specchio
        // input è l'immagine in input, non l'immagine specchiata
        typename ImageType::RegionType inputRegion = input->GetLargestPossibleRegion();
        typename ImageType::IndexType regionIndex;
        regionIndex.Fill(0);
        typename ImageType::RegionType outputRegion(regionIndex,inputRegion.GetSize());
        return outputRegion;
    }
    /*!
     *
     */
    template<typename ImageType,typename PointerType>
    void getGLCM(PointerType image,int (&data)[4][4],const int distance = 1) {
        // restituisce la GLCM per side effect
        // image è l'immagine in input
        // data è la GLCM creata per side effect
        // distance è la distance to GLCM, di default a 1
        typedef itk::Statistics::ScalarImageToCooccurrenceMatrixFilter<ImageType> Image2CoOccuranceType;
        typename Image2CoOccuranceType::Pointer glcmGenerator = Image2CoOccuranceType::New();
        glcmGenerator->SetNumberOfBinsPerAxis(4);
        glcmGenerator->SetInput(image);
        const int dimension = ImageType::GetImageDimension();
        // CLGM orizzontale
        typename ImageType::OffsetType horizontalOffset;
        horizontalOffset[0]=distance;
        horizontalOffset[1]=0;
        if(dimension==3)
            horizontalOffset[2]=0;
        glcmGenerator->SetOffset(horizontalOffset);
        glcmGenerator->Update();
        typename Image2CoOccuranceType::HistogramType::ConstPointer horizontalHistogram = glcmGenerator->GetOutput();
        // CLGM verticale
        typename ImageType::OffsetType verticalOffset;
        verticalOffset[0]=0;
        verticalOffset[1]=distance;
        if(dimension==3)
            verticalOffset[2]=0;
        glcmGenerator->SetOffset(verticalOffset);
        glcmGenerator->Update();
        typename Image2CoOccuranceType::HistogramType::ConstPointer verticalHistogram = glcmGenerator->GetOutput();
        // converto la GLCM in un array di int
        for(int i = 0; i < 4; ++i) {
            for(int j=0; j < 4;j++) {
                typename Image2CoOccuranceType::HistogramType::IndexType index(2);
                index[0] = i;
                index[1] = j;
                int horizontal = static_cast<int>(horizontalHistogram->GetFrequency(index));
                int vertical = static_cast<int>(verticalHistogram->GetFrequency(index));
                data[i][j] = roundToInt(static_cast<double>(horizontal+vertical)/2);
            }
        }
    }
    /*!
     *
     */
    template<typename ImagePointer,typename ImageType,typename SimplePointer,typename SimpleType>
    double** applyFirstOrderFeature(ImagePointer input,ImagePointer output,SimplePointer mask,romeo::model::protocols::features::FirstOrderFeature* feature) {

        // input è l'immagine in ingresso
        // output è l'immagine in uscita
        // mask è la maschera
        // feature è la feature da eseguire

        typedef double (*MyPrototype)(double* data,int size,int dimension);
        MyPrototype featureExtractor = (MyPrototype) QLibrary::resolve(feature->getDynamicLibraryPath(),feature->getDynamicFunctionName().toStdString().c_str());
        if(!featureExtractor){
            qDebug () << "NOT FIND LIB";
        }
        int dimension = ImageType::GetImageDimension();
        // imposta raggio della finestra scorrevole: raggio = 1 -> finestra = 3
        typename ImageType::SizeType radius;
        radius.Fill(windowSize/2);
        ImagePointer mirror = createMirror<ImagePointer,ImageType>(input,windowSize/2);
        typename ImageType::RegionType outputRegion = getRegion<ImagePointer,ImageType>(input);

        // iteratore per l'immagine in input
        itk::NeighborhoodIterator<ImageType> inputIterator(radius, mirror , outputRegion);
        inputIterator.NeedToUseBoundaryConditionOff();
        // iteratore per l'immagine in output
        itk::ImageRegionIterator<ImageType> outputIterator(output , output->GetLargestPossibleRegion());
        // iteratore per la maschera
        itk::ImageRegionIterator<SimpleType> maskIterator;
        if(mask.IsNotNull())
            maskIterator = itk::ImageRegionIterator<SimpleType>(mask , mask->GetLargestPossibleRegion());

        // allocazione degli array di double da restituire per l'eventuale algoritmo di clustering
        const int length = input->GetLargestPossibleRegion().GetNumberOfPixels();
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
                //cout << "Completato al " << (static_cast<double>(index)/length)*100 << "%\n";
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
                //cout << "Completato al " << (static_cast<double>(index)/length)*100 << "%\n";
            }
        }
        // creazione immagine output
        createImage(outputIterator,result,length);
        // ritorna gli array di double per l'algoritmo di clustering
        return result;
    }
    /*!
     *
     */
    template<typename PointerType,typename ImageType,typename SimplePointerType,typename SimpleType>
    double** applySecondOrderFeature(PointerType input,PointerType output,SimplePointerType mask,int distance,romeo::model::protocols::features::SecondOrderFeature* feature) {

        // input è l'immagine in ingresso
        // output è l'immagine in uscita
        // mask è la maschera
        // distance è la distanza dalla GLCM

        typedef double (*MyPrototype)(int data[4][4]);
        MyPrototype featureExtractor = (MyPrototype) QLibrary::resolve(feature->getDynamicLibraryPath(),feature->getDynamicFunctionName().toStdString().c_str());

        int dimension = ImageType::GetImageDimension();
        // imposta raggio della finestra scorrevole: raggio = 1 -> finestra = 3
        typename ImageType::SizeType radius;
        radius.Fill(windowSize/2);

        PointerType mirror = createMirror<PointerType,ImageType>(input,windowSize/2);
        typename ImageType::RegionType outputRegion = getRegion<PointerType,ImageType>(input);

        // iteratore per l'immagine in input
        itk::NeighborhoodIterator<ImageType> inputIterator(radius, mirror , outputRegion);
        inputIterator.NeedToUseBoundaryConditionOff();
        // iteratore per l'immagine in output
        itk::ImageRegionIterator<ImageType> outputIterator(output , output->GetLargestPossibleRegion());
        // iteratore per la maschera
        itk::ImageRegionIterator<SimpleType> maskIterator;
        if(mask.IsNotNull())
            maskIterator = itk::ImageRegionIterator<SimpleType>(mask , mask->GetLargestPossibleRegion());

        // allocazione dell'array di double da restituire per l'eventuale algoritmo di clustering
        const int length = input->GetLargestPossibleRegion().GetNumberOfPixels();
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
                        typename SimpleType::IndexType regionIndex;
                        regionIndex.Fill(0);
                        typename SimpleType::SizeType regionSize;
                        regionSize.Fill(windowSize);
                        typename SimpleType::RegionType region(regionIndex,regionSize);
                        // istanzio una nuova immagine
                        SimplePointerType neighbor = SimpleType::New();
                        neighbor->SetRegions(region);
                        neighbor->Allocate();
                        // la riempio con i valori dell'iteratore
                        itk::ImageRegionIterator<SimpleType> pieceIterator(neighbor , neighbor->GetLargestPossibleRegion());
                        for(int i=0;i<static_cast<int>(pow(windowSize,dimension));i++) {
                            pieceIterator.Set(inputIterator.GetPixel(i)[color]);
                            ++pieceIterator;
                        }
                        // procuro la GLCM
                        int data[4][4];
                        getGLCM<SimpleType,SimplePointerType>(neighbor,data,distance);
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
                //cout << "Completato al " << (static_cast<double>(index)/length)*100 << "%\n";
            }
        }
        else {
            // ignoro la mask
            int index =0;
            while(!inputIterator.IsAtEnd()) {
                for(int color=0;color<3;color++) {
                    // definisco una regione
                    typename SimpleType::IndexType regionIndex;
                    regionIndex.Fill(0);
                    typename SimpleType::SizeType regionSize;
                    regionSize.Fill(windowSize);
                    typename SimpleType::RegionType region(regionIndex,regionSize);
                    // istanzio una nuova immagine
                    SimplePointerType neighbor = SimpleType::New();
                    neighbor->SetRegions(region);
                    neighbor->Allocate();
                    // la riempio con i valori dell'iteratore
                    itk::ImageRegionIterator<SimpleType> pieceIterator(neighbor , neighbor->GetLargestPossibleRegion());
                    for(int i=0;i<static_cast<int>(pow(windowSize,dimension));i++) {
                        pieceIterator.Set(inputIterator.GetPixel(i)[color]);
                        ++pieceIterator;
                    }
                    // procuro la GLCM
                    int data[4][4];
                    getGLCM<SimpleType,SimplePointerType>(neighbor,data,distance);
                    // diamo l'array in pasto alla feature di secondo ordine
                    double value = featureExtractor(data);
                    result[color][index] = value;
                }
                ++inputIterator;
                ++index;
                //cout << "Completato al " << (static_cast<double>(index)/length)*100 << "%\n";
            }
        }
        // creazione immagine output
        createImage(outputIterator,result,length);
        // ritorna gli array di double per l'algoritmo di clustering
        return result;
    }
    /*!
     *
     */
    template<int dimensions>
    void templateExecute(romeo::model::datasets::AbstractSubject *subject,QString path,bool saveFeatures,QString outputFormat) {
        // il path viene aggiustato rispetto ai corretti separatori in base al sistema operativo
        path = QDir::toNativeSeparators(path + "/");
        if(outputFormat== "INPUT")
            outputFormat = QString(".") + subject->getSubject().split(".").takeLast();
        typedef unsigned char MaskPixelType;
        typedef itk::Image< MaskPixelType, dimensions > MaskImageType;
        typedef itk::RGBPixel<unsigned char> RGBPixelType;//Pixel Type
        typedef itk::Image< RGBPixelType, dimensions > RGBImageType;//Image Type
        romeo::model::imageIO::HandlerIOStatic* imageHandler = romeo::model::imageIO::HandlerIOStatic::getInstance();
        typename RGBImageType::Pointer imagePointer = imageHandler->readImage<typename RGBImageType::Pointer,RGBImageType>(subject->getSubject());
        typename MaskImageType::Pointer maskPointer = imageHandler->readImage<typename MaskImageType::Pointer,MaskImageType>(subject->getMask());
        QList<romeo::model::protocols::features::AbstractFeature*> featureList = getFeatures();
        int numberOfRows,numberOfColumns;
        double** result;
        if(featureList.size()>0) {
            qDebug() << "Ci sono features da estrarre";
            // ci sono features da estrarre
            numberOfRows = imagePointer->GetLargestPossibleRegion().GetNumberOfPixels();
            numberOfColumns = 3*featureList.size();
            result = new double*[numberOfColumns];
            int index = 0;
            for(int i=0;i<featureList.size() && !getStopAnalysis();i++) {

                typename RGBImageType::Pointer outputFeature = RGBImageType::New();
                outputFeature->SetRegions(imagePointer->GetLargestPossibleRegion());
                outputFeature->Allocate();
                romeo::model::protocols::features::AbstractFeature* currentFeature = featureList[i];
                double** singleFeature;
                romeo::model::protocols::features::FirstOrderFeature* firstOrderFeature = dynamic_cast<romeo::model::protocols::features::FirstOrderFeature*>(featureList[i]);
                if(firstOrderFeature) {
                    qDebug() << "Feature del primo ordine";
                    singleFeature = applyFirstOrderFeature<typename RGBImageType::Pointer,RGBImageType,typename MaskImageType::Pointer,MaskImageType>(imagePointer,outputFeature,maskPointer,firstOrderFeature);
                    qDebug() << "Calcolata feature primo ordine";
                }
                else {
                    qDebug() << "Feature del secondo ordine";
                    romeo::model::protocols::features::SecondOrderFeature* secondOrderFeature = dynamic_cast<romeo::model::protocols::features::SecondOrderFeature*>(featureList[i]);
                    if(secondOrderFeature)
                        singleFeature = applySecondOrderFeature<typename RGBImageType::Pointer,RGBImageType,typename MaskImageType::Pointer,MaskImageType>(imagePointer,outputFeature,maskPointer,distanceToGLCM,secondOrderFeature);
                }
                // singleFeature è una matrice [ncols][nrows]
                for(int j=0;j<3;j++) {
                    result[index]=singleFeature[j];
                    ++index;
                }
                if(saveFeatures) {
                    qDebug() << "Salva";
                    QString fileName = QUrl::fromLocalFile(subject->getName() + "_" + currentFeature->getName()).path();
                    imageHandler->writeImage<typename RGBImageType::Pointer,RGBImageType>(outputFeature,fileName,path,outputFormat);
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
            qDebug() << "Non ci sono feature da estrarre";
            numberOfRows = imagePointer->GetLargestPossibleRegion().GetNumberOfPixels();
            numberOfColumns = 3;
            result = readImage<typename RGBImageType::Pointer,RGBImageType>(imagePointer);
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
                qDebug() << "Siamo dentro all'algoritmo";
                // c'è effettivamente un algoritmo da eseguire
                // creazione maschera
                int* mask = getMask<typename MaskImageType::Pointer,MaskImageType>(maskPointer,numberOfRows);
                // creazione clusterid
                int* clusterid = new int[numberOfRows];
                qDebug() << "Prima algoritmo";
                algorithmToExecute->execute(transponse,mask,numberOfRows,numberOfColumns,clusterid,getNClusters(),getAlgorithmParameters());
                qDebug() << "Finito l'algoritmo";
                // creazione immagine di output
                typename RGBImageType::Pointer output = RGBImageType::New();
                output->SetRegions(imagePointer->GetLargestPossibleRegion());
                output->Allocate();
                qDebug() << "Prima crezione immagine";
                createClusteringImage<typename RGBImageType::Pointer,RGBImageType,RGBPixelType>(output,clusterid,mask);
                qDebug() << "Dopo creazione immagine";
                // delete dei dati sullo heap
                delete[] mask;
                delete[] clusterid;
                // scrivi l'immagine
                QString fileName = QUrl::fromLocalFile(subject->getName() + "_" + algorithmToExecute->getName()).path();
                imageHandler->writeImage<typename RGBImageType::Pointer,RGBImageType>(output,fileName,path,outputFormat);
                emit algorithmExecuted(path + fileName + outputFormat);
            }
            // delete dei dati
            for(int i=0;i<numberOfRows;i++)
                delete[] transponse[i];
            delete[] transponse;
        }

    }


private:
    /*!
     * \brief windowSize Campo dati che indica la dimensione della finestra di pixel da analizzare.
     */
    int windowSize;
    /*!
     * \brief distanceToGLCM Valore richiesto per il calcolo della matrice GLCM.
     */
    int distanceToGLCM;


};
}}}
#endif // STATICPROTOCOL_H
