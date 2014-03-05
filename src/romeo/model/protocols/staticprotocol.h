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
// ITK
#include "itkImage.h"
#include "itkRGBPixel.h"
#include "itkNeighborhoodIterator.h"
#include "itkMirrorPadImageFilter.h"
//
#include <src/romeo/model/inputformats.h>
#include <src/romeo/model/imageIO/handleriostatic.h>
#include <src/romeo/model/protocols/features/firstorderfeature.h>
#include <src/romeo/model/protocols/features/abstractfeature.h>

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
    StaticProtocol(QString nomeP, QString desc, algorithms::AbstractAlgorithm* alg, int clusterNum, QList<QString> algParameters, QList<features::AbstractFeature*> feat, bool testProtocol, int window=3, int distance=1);
    /*!
     * \brief Override del metodo execute della classe astratta AbstractProtocol
     * \param Il soggetto utilizzato per eseguire l'analisi, deve contenere un immagine di tipo statico
     */
    virtual void execute(datasets::AbstractSubject *subject);
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
    int roundToInt(double num);
    /*!
     *
     */
    int* normalize(double* array,int length);
    /*!
     *
     */
    double** transform(double** result,const int nrows,const int ncolumns);
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
    template<typename ImagePointer,typename ImageType,typename SimplePointer,typename SimpleType>
    double** applyFirstOrderFeature(ImagePointer input,ImagePointer output,SimplePointer mask,romeo::model::protocols::features::FirstOrderFeature* feature) {

        // input è l'immagine in ingresso
        // output è l'immagine in uscita
        // mask è la maschera
        // feature è la feature da eseguire

        typedef int (*MyPrototype)(double* data,int size,int dimension);
        MyPrototype featureExtractor = (MyPrototype) QLibrary::resolve(feature->getDynamicLibraryPath(),feature->getDynamicFunctionName().toStdString().c_str());

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
        return transform(result,length,3);
    }
    /*!
     *
     */
    template<int dimensions>
    void templateExecute(romeo::model::datasets::AbstractSubject *subject) {
        typedef unsigned char MaskPixelType;
        typedef itk::Image< MaskPixelType, dimensions > MaskImageType;
        typedef itk::RGBPixel<unsigned char> RGBPixelType;//Pixel Type
        typedef itk::Image< RGBPixelType, dimensions > RGBImageType;//Image Type
        romeo::model::imageIO::HandlerIOStatic* imageReader = romeo::model::imageIO::HandlerIOStatic::getInstance();
        typename RGBImageType::Pointer imagePointer = imageReader->readImage<typename RGBImageType::Pointer,RGBImageType>(subject->getSubject());
        typename MaskImageType::Pointer maskPointer = imageReader->readImage<typename MaskImageType::Pointer,MaskImageType>(subject->getMask());
        QList<romeo::model::protocols::features::AbstractFeature*> featureList = getFeatures();
        for(int i=0;i<featureList.size();i++) {
            typename RGBImageType::Pointer outputFeature = RGBImageType::New();
            outputFeature->SetRegions(imagePointer->GetLargestPossibleRegion());
            outputFeature->Allocate();
            romeo::model::protocols::features::FirstOrderFeature* currentFeature = dynamic_cast<romeo::model::protocols::features::FirstOrderFeature*>(featureList[i]);
            if(currentFeature)
                applyFirstOrderFeature<typename RGBImageType::Pointer,RGBImageType,typename MaskImageType::Pointer,MaskImageType>(imagePointer,outputFeature,maskPointer,currentFeature);
            else {

            }
        }
    }
private:
    int windowSize;
    int distanceToGLCM;

};
}}}
#endif // STATICPROTOCOL_H
