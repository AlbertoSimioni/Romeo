/**
* \file dynamicprotocol.h
* \author Matteo Pozza
* \date 2014-02-17
**
* \brief Header della classe DynamicProtocol del package romeo::model::protocols
*/

#ifndef DYNAMICPROTOCOL_H
#define DYNAMICPROTOCOL_H
#include "abstractprotocol.h"
// PROGRAMMA
#include <src/romeo/model/inputformats.h>
#include <src/romeo/model/imageIO/handleriodynamic.h>
#include <src/romeo/model/protocols/features/dynamicfeature.h>
#include <src/romeo/model/protocols/features/abstractfeature.h>
#include <src/romeo/model/protocols/algorithms/abstractalgorithm.h>

namespace romeo {
namespace model {
namespace protocols{

/**
 * \brief La classe DynamicProtocol rappresenta i protocolli che agiscono su immagini di tipo dinamico,
 **
 *  e quindi accettano soggetti di tipo Subject2D col tempo e Subject3D col tempo.
 */
class DynamicProtocol : public AbstractProtocol
{
    typedef unsigned char MaskPixelType;
    typedef itk::Image< MaskPixelType, 2 > Mask2DType;
    typedef itk::Image< MaskPixelType, 3 > Mask3DType;
    typedef itk::RGBPixel<unsigned char> RGBPixelType;
    typedef itk::Image< RGBPixelType, 2 > Image2DType;
    typedef itk::Image< RGBPixelType, 3 > Image3DType;
    typedef itk::Image< RGBPixelType, 4 > Image4DType;
public:
    /*!
     * \brief Costruisce un nuovo protocollo che opera su immagini dinamiche.
     * \param nomeP Nome del protocollo.
     * \param desc Descrizione del protocollo.
     * \param alg Algoritmo di clustering associato al protocollo.
     * \param clusterNum Numero di cluster con cui deve operare l'algoritmo.
     * \param algParameters Valori associati ai parametri dell'algoritmo.
     * \param feat Lista delle feature che il protocollo esegue.
     * \param testProtocol Valore booleano che indica se il protocollo è di test.
     */
    DynamicProtocol(QString nomeP, QString desc, algorithms::AbstractAlgorithm* alg, int clusterNum, QList<QString> algParameters, QList<features::AbstractFeature*> feat,bool testProtocol);
    /*!
     * \brief Si preoccupa di convertire un video 2D in una matrice di valori double
     * \param video Video 2D da convertire
     */
    double** read2DVideo(cv::VideoCapture video);
    /*!
     * \brief Si preoccupa di convertire un video 3D in una matrice di valori double
     * \param video Video 3D da convertire
     */
    double** read3DVideo(Image4DType::Pointer video);
    /*!
     * \brief Applica una feature dinamica ad un video 2D
     * \param video Video 2D da cui estrarre la feature
     * \param output Immagine in output dall'estrazione della feature
     * \param mask Immagine utilizzata come maschera per il video in ingresso
     * \param feature Feature da estrarre
     */
    double** apply2DDynamicFeature(cv::VideoCapture video,Image2DType::Pointer output,Mask2DType::Pointer mask,romeo::model::protocols::features::DynamicFeature* feature);
    /*!
     * \brief Applica una feature dinamica ad un video 3D
     * \param video Video 3D da cui estrarre la feature
     * \param output Immagine in output dall'estrazione della feature
     * \param mask Immagine utilizzata come maschera per il video in ingresso
     * \param feature Feature da estrarre
     */
    double** apply3DDynamicFeature(Image4DType::Pointer video,Image3DType::Pointer output,Mask3DType::Pointer mask,romeo::model::protocols::features::DynamicFeature* feature);
    /*!
     * \brief Esegue un protocollo su di un video 2D
     * \param subject Il soggetto su cui viene eseguito il protocollo
     * \param path Il percorso di salvataggio dei file.
     * \param saveFeatures Se è true indica che vanno salvate le immagini risultato dell'estrazione di feature.
     * \param outputFormat Il formato di salvataggio dei dati.
     */
    void video2DExecute(datasets::AbstractSubject *subject,QString path,bool saveFeatures,QString outputFormat);
    /*!
     * \brief Esegue un protocollo su di un video 3D
     * \param subject Il soggetto su cui viene eseguito il protocollo
     * \param path Il percorso di salvataggio dei file.
     * \param saveFeatures Se è true indica che vanno salvate le immagini risultato dell'estrazione di feature.
     * \param outputFormat Il formato di salvataggio dei dati.
     */
    void video3DExecute(datasets::AbstractSubject *subject,QString path,bool saveFeatures,QString outputFormat);
    /*!
     * \brief Override del metodo execute della classe astratta AbstractProtocol
     * \param subject Il soggetto su cui viene eseguito il protocollo
     * \param path Il percorso di salvataggio dei file.
     * \param saveFeatures Se è true indica che vanno salvate le immagini risultato dell'estrazione di feature.
     * \param outputFormat Il formato di salvataggio dei dati.
     */
    virtual void execute(datasets::AbstractSubject *subject,QString path,bool saveFeatures,QString outputFormat);
    /*!
     * \brief Funzione virtuale che ritorna il tipo del protocollo corrente, per la classe DynamicProtocol ritornerà ProtocolType::DYNAMIC. La funzione è override di quella definita nella superclasse e può essere chiamata avendo solo un riferimento a AbstractProtocol.
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

};
}}}
#endif // DYNAMICPROTOCOL_H
