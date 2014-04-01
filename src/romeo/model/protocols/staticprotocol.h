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
#include "itkMirrorPadImageFilter.h"
#include "itkScalarImageToCooccurrenceMatrixFilter.h"
//
#include <src/romeo/model/inputformats.h>
#include <src/romeo/model/imageIO/handleriostatic.h>
#include <src/romeo/model/protocols/features/firstorderfeature.h>
#include <src/romeo/model/protocols/features/secondorderfeature.h>
#include <src/romeo/model/protocols/features/abstractfeature.h>
#include <src/romeo/model/protocols/algorithms/abstractalgorithm.h>

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
     * \param subject Il soggetto su cui viene eseguito il protocolli
     * \param path Il percorso di salvataggio dei file.
     * \param saveFeatures Se è true indica che vanno salvate le immagini risultato dell'estrazione di feature.
     * \param outputFormat Il formato di salvataggio dei dati.
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
     * \brief Ritorna l'indice del frame da cui iniziare le analisi (incluso)
     */
    virtual int getFrameInit() const;
    /*!
     * \brief Ritorna l'indice del frame in cui terminare le analisi (incluso)
     */
    virtual int getFrameEnd() const;
    /*!
     * \brief Metodo per la creazione di una immagine con pad di pixel a specchio
     * \param input è l'immagine in input.
     * \param pad è il numero di pixel di cui si vuole fare il pad (generalmente metà della taglia della finestra scorrevole).
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
     * \brief restituisce la regione di interesse relativa all'immagine con pad a specchio
     * \param input L'immagine in input, non l'immagine specchiata
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
     * \brief Metodo che ritorna la matrice GLCM per side effect tramite il parametro di input data
     * \param image Immagine di input.
     * \param data Riferimento alla GLCM da modificare.
     * \param distance Distanza dalla GLCM necessario per il calcolo, di default a uno.
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
     * \brief Metodo template che applica un'operazione di estrazione di feature a un'immagine data in input e restituisce in output il risultato dell'operazione. La funzione prende come parametro la feature di primo ordine che si vuole estrarre.
     * \param input L'immagine su cui eseguire l'analisi.
     * \param output L'immagine risultato dell'operazione di estrazione.
     * \param mask Maschera dell'immagine.
     * \param feature Feature da applicare all'immagine.
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

        // numero di pixel
        const int length = input->GetLargestPossibleRegion().GetNumberOfPixels();

        // iteratore per la maschera
        itk::ImageRegionIterator<SimpleType> maskIterator;
        // maschera in un array: servirà per createImage
        int* maskArray;
        if(mask.IsNotNull()) {
            maskIterator = itk::ImageRegionIterator<SimpleType>(mask , mask->GetLargestPossibleRegion());
            maskArray = getMask<typename SimpleType::Pointer,SimpleType>(mask,length);
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
                //qDebug() << "Completato al " << (static_cast<double>(index)/length)*100 << "%\n";
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
                //qDebug() << "Completato al " << (static_cast<double>(index)/length)*100 << "%\n";
            }
        }
        // creazione immagine output
        createImage(outputIterator,result,maskArray,length);
        // cancellazione della maschera
        delete[] maskArray;
        // ritorna gli array di double per l'algoritmo di clustering
        return result;
    }

    /*!
     * \brief Metodo template che applica un'operazione di estrazione di feature a un'immagine data in input e restituisce in output il risultato dell'operazione. La funzione prende come parametro la feature di secondo ordine che si vuole estrarre.
     * \param input L'immagine di input da analizzare.
     * \param output L'immagine risultato dell'operazione di estrazione.
     * \param mask Maschera dell'immagine.
     * \param distance Parametro per indicare la distanza dalla GLCM con cui calcolare la feature.
     * \param feature Feature da applicare all'immagine.
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

        // numero di pixel
        const int length = input->GetLargestPossibleRegion().GetNumberOfPixels();

        // iteratore per la maschera
        itk::ImageRegionIterator<SimpleType> maskIterator;
        // maschera in un array: servirà per createImage
        int* maskArray;
        if(mask.IsNotNull()) {
            maskIterator = itk::ImageRegionIterator<SimpleType>(mask , mask->GetLargestPossibleRegion());
            maskArray = getMask<typename SimpleType::Pointer,SimpleType>(mask,length);
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
                //qDebug() << "Completato al " << (static_cast<double>(index)/length)*100 << "%\n";
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
                //qDebug() << "Completato al " << (static_cast<double>(index)/length)*100 << "%\n";
            }
        }
        // creazione immagine output
        createImage(outputIterator,result,maskArray,length);
        // cancellazione della maschera
        delete[] maskArray;
        // ritorna gli array di double per l'algoritmo di clustering
        return result;
    }
    /*!
     * \brief Metodo che esegue il protocollo sul subject passato in input. Il metodo è template perchè va istanziato con un valore intero indicante se l'immagine è 2D o 3D.
     * \param subject Subject da analizzare
     * \param path Percorso in cui salvare i risultati dell'operazione.
     * \param saveFeatures Valore booleano che è true se si vogliono salvare su disco i risultati dell'estrazione di feature, false altrimenti.
     * \param outputFormat Formato immagine con cui esportare i risultati dell'analisi
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
            int requestedMemory = numberOfRows*numberOfColumns;
            // se la memoria richiesta è eccessiva lancia una eccezione
            checkRequestedMemory(requestedMemory);
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
            int requestedMemory = numberOfRows*numberOfColumns;
            // se la memoria richiesta è eccessiva lancia una eccezione
            checkRequestedMemory(requestedMemory);
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
