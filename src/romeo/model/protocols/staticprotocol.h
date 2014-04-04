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

    /*typedef unsigned char MaskPixelType;
    typedef itk::RGBPixel<unsigned char> Image2DPixelType;
    typedef double Image3DPixelType;
    typedef itk::Image< MaskPixelType, 2 > Mask2DType;
    typedef itk::Image< MaskPixelType, 3 > Mask3DType;
    typedef itk::Image< Image2DPixelType, 2 > Image2DType;
    typedef itk::Image< Image3DPixelType, 3 > Image3DType;*/

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
        if(dimension == 3) {
            // trovo minimo e massimo da impostare per il calcolo della glcm
            double min,max;
            bool firstTime = true;
            typename itk::ImageRegionIterator<ImageType> iterator(image,image->GetLargestPossibleRegion());
            while(!iterator.IsAtEnd()) {
                if(firstTime) {
                    min = static_cast<double>(iterator.Get());
                    max = static_cast<double>(iterator.Get());
                    firstTime = false;
                }
                else {
                    if(min > static_cast<double>(iterator.Get()))
                        min = static_cast<double>(iterator.Get());
                    if(max < static_cast<double>(iterator.Get()))
                        max = static_cast<double>(iterator.Get());
                }
                ++iterator;
            }
            glcmGenerator->SetPixelValueMinMax(min,max);
        }
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
    double** read2DImage(Image2DType::Pointer input);
    /*!
     *
     */
    double** read3DImage(Image3DType::Pointer input);
    /*!
     * \brief Metodo che applica un'operazione di estrazione di feature di primo ordine a un'immagine 2D data in input e restituisce in output il risultato dell'operazione. La funzione prende come parametro la feature di primo ordine che si vuole estrarre.
     * \param input L'immagine su cui eseguire l'analisi.
     * \param output L'immagine risultato dell'operazione di estrazione.
     * \param mask Maschera dell'immagine.
     * \param feature Feature da applicare all'immagine.
     */
    double** applyFirstOrderFeature2D(Image2DType::Pointer input,Image2DType::Pointer output,Mask2DType::Pointer mask,romeo::model::protocols::features::FirstOrderFeature* feature);
    /*!
     * \brief Metodo template che applica un'operazione di estrazione di feature di primo ordine a un'immagine 3D data in input e restituisce in output il risultato dell'operazione. La funzione prende come parametro la feature di primo ordine che si vuole estrarre.
     * \param input L'immagine su cui eseguire l'analisi.
     * \param output L'immagine risultato dell'operazione di estrazione.
     * \param mask Maschera dell'immagine.
     * \param feature Feature da applicare all'immagine.
     */
    double* applyFirstOrderFeature3D(Image3DType::Pointer input,Image3DType::Pointer output,Mask3DType::Pointer mask,romeo::model::protocols::features::FirstOrderFeature* feature);
    /*!
     * \brief Metodo template che applica un'operazione di estrazione di feature di secondo ordine a un'immagine 2D data in input e restituisce in output il risultato dell'operazione. La funzione prende come parametro la feature di secondo ordine che si vuole estrarre.
     * \param input L'immagine su cui eseguire l'analisi.
     * \param output L'immagine risultato dell'operazione di estrazione.
     * \param mask Maschera dell'immagine.
     * \param feature Feature da applicare all'immagine.
     */
    double** applySecondOrderFeature2D(Image2DType::Pointer input,Image2DType::Pointer output,Mask2DType::Pointer mask,int distance, romeo::model::protocols::features::SecondOrderFeature* feature);
    /*!
     * \brief Metodo template che applica un'operazione di estrazione di feature di secondo ordine a un'immagine 3D data in input e restituisce in output il risultato dell'operazione. La funzione prende come parametro la feature di secondo ordine che si vuole estrarre.
     * \param input L'immagine su cui eseguire l'analisi.
     * \param output L'immagine risultato dell'operazione di estrazione.
     * \param mask Maschera dell'immagine.
     * \param feature Feature da applicare all'immagine.
     */
    double* applySecondOrderFeature3D(Image3DType::Pointer input,Image3DType::Pointer output,Mask3DType::Pointer mask, int distance, romeo::model::protocols::features::SecondOrderFeature* feature);
    /*!
     * \brief Metodo per l'analisi di una immagine 2D
     * \param subject Subject da analizzare
     * \param path Percorso in cui salvare i risultati dell'operazione.
     * \param saveFeatures Valore booleano che è true se si vogliono salvare su disco i risultati dell'estrazione di feature, false altrimenti.
     * \param outputFormat Formato immagine con cui esportare i risultati dell'analisi
     */
    void image2DExecute(romeo::model::datasets::AbstractSubject *subject,QString path,bool saveFeatures,QString outputFormat);
    /*!
     * \brief Metodo per l'analisi di una immagine 3D
     * \param subject Subject da analizzare
     * \param path Percorso in cui salvare i risultati dell'operazione.
     * \param saveFeatures Valore booleano che è true se si vogliono salvare su disco i risultati dell'estrazione di feature, false altrimenti.
     * \param outputFormat Formato immagine con cui esportare i risultati dell'analisi
     */
    void image3DExecute(romeo::model::datasets::AbstractSubject *subject,QString path,bool saveFeatures,QString outputFormat);


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
