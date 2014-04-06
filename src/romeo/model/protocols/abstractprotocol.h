/**
* \file abstractprotocol.h
* \author Matteo Pozza
* \date 2014-02-17
**
* \brief Header della classe AbstractProtocol del package romeo::model::protocols
*/


#ifndef ABSTRACTPROTOCOL_H
#define ABSTRACTPROTOCOL_H
#include<QString>
#include<QList>
#include <QObject>
// ITK
#include "itkImage.h"
#include "itkRGBPixel.h"
#include "itkNeighborhoodIterator.h"
#include "itkImageRegionIterator.h"

#include "algorithms/abstractalgorithm.h"
#include "features/abstractfeature.h"
#include "../datasets/abstractsubject.h"
#include <src/romeo/model/protocols/color.h>

namespace romeo {
namespace model {
namespace protocols{

/*!
 * \brief Enumerazione che rappresenta i tipi di protocollo disponibili: STATIC e DYNAMIC.
 */
enum ProtocolType{STATIC,DYNAMIC};

/**
 * \brief a classe astratta AbstractProtocol rappresenta un protocollo eseguibile dall'utente
 *
 * La classe contiene metodi per modificare le feature e gli algoritmi di clustering definiti per il protocollo e i metodi per eseguire le funzionalità sui dati passati.
 *
 */
class AbstractProtocol : public QObject
{
    Q_OBJECT

protected:
    typedef unsigned char MaskPixelType;
    typedef itk::RGBPixel<unsigned char> Image2DPixelType;
    typedef double Image3DPixelType;
    typedef itk::Image< MaskPixelType, 2 > Mask2DType;
    typedef itk::Image< MaskPixelType, 3 > Mask3DType;
    typedef itk::Image< Image2DPixelType, 2 > Image2DType;
    typedef itk::Image< Image3DPixelType, 3 > Image3DType;
    typedef itk::Image< Image2DPixelType, 3 > ClusteringImage3DType;
    typedef itk::Image< Image3DPixelType, 4 > Image4DType;

public:
    /*!
     * \brief Costruisce un nuovo protocollo con l''algoritmo e le features indicate
     * \param nomeP Nome del protocollo da costruire
     * \param desc La descrizione del protocollo sotto forma di stringa
     * \param alg Un puntatore all'algoritmo di clustering che il protocollo deve eseguire
     * \param clusterNum Parametro che indica il numero di cluster che deve generare l'algoritmo.
     * \param parameters Lista dei valori dei parametri dell'algoritmo associato al protocollo.
     * \param feat Un vettore di puntatori a features che fanno parte del protocollo.
     * \param testProtocol Valore booleano che indica se il protocollo è di test.
     */
    AbstractProtocol(QString nomeP, QString desc, algorithms::AbstractAlgorithm* alg, int clusterNum, QList<QString> parameters, QList<features::AbstractFeature*>& feat,bool testProtocol);
    /*!
     * \brief Sostituisce la lista delle feature che il protocollo possiede con quella indicata. Si può modificare la lista delle feature solo se il protocollo corrente è un protocollo di test
     * \param feat Lista di features che si vogliono inserire nel protocollo
     * \return Ritorna true se la modifica è avvenuta correttamente, false se si è cercati di modificare un protocollo non di test.
     */
    bool setFeatures(QList<features::AbstractFeature*>& feat);
    /*!
     * \brief Inserisce nel protocollo l'algoritmo di clustering indicato, sostituendo quello attualmente in uso
     * \param alg puntatore all'algoritmo di clustering
     */
    bool setAlgorithm(algorithms::AbstractAlgorithm* alg);
    /*!
     * \brief Modifica lo stato del protocollo da "test" a "ufficiale"
     * \return Ritorna true se la modifica è avvenuta con successo, false nel caso il protocollo fosse già in stato "ufficiale"
     */
    bool setOfficial();
    /*!
     * \brief Esegue il protocollo sul soggetto passato come puntatore
     * \param subject Il soggetto su cui viene eseguito il protocolli
     * \param path Il percorso di salvataggio dei file.
     * \param saveFeatures Se è true indica che vanno salvate le immagini risultato dell'estrazione di feature.
     * \param outputFormat Il formato di salvataggio dei dati.
     */
    virtual void execute(datasets::AbstractSubject *subject,QString path,bool saveFeatures,QString outputFormat) = 0;
    /*!
     * \brief Metodo virtuale puro che ritorna il tipo del protocollo, determinato dinamicamente.
     */
    virtual ProtocolType getType() = 0;
    //virtual void featureExtract() = 0;
    /*!
     * \brief Ritorna la dimensione della finestra su cui vengono eseguite le operazioni.
     */
    virtual int getWindowSize() const = 0;
    /*!
     * \brief Ritorna un intero che indica la dimensione della GLCM(Gray Level Concurrency Matrix).
     */
    virtual int getDistanceToGlcm() const = 0;
    /*!
     * \brief Metodo che ritorna l'indice del frame iniziale (incluso)
     */
    virtual int getFrameInit() const = 0;
    /*!
     * \brief Metodo che ritorna l'indice del frame finale (incluso)
     */
    virtual int getFrameEnd() const = 0;
    /*!
     * \brief Ritorna il nome del protocollo.
     */
    QString getName() const;
    /*!
     * \brief Ritorna la descrizione del protocollo.
     */
    QString getDescription() const;
    /*!
     * \brief Ritorna un valore booleano: vero se il protocollo è di test, falso altrimenti.
     */
    bool getTest() const;
    /*!
     * \brief Ritorna un puntatore all'algoritmo di clustering del protocollo. Il puntatore è nullo se nessun algoritmo è stato ancora caricato.
     */
    algorithms::AbstractAlgorithm* getAlgorithm() const;
    /*!
     * \brief Ritorna una lista contenente i puntatori ai feature extractor selezionati per il protocollo.
     */
    QList<protocols::features::AbstractFeature*> getFeatures() const;
    /*!
     * \brief Ritorna una lista contenente i nomi delle feature selezionate per il protocollo.
     */
    QStringList getFeaturesName() const;
    /*!
     * \brief Ritorna il nome dell'algoritmo caricato nel protocollo.
     */
    QString getAlgorithmName() const;
    /*!
     * \brief Ritorna il numero di cluster che attualmente viene generato dall'algoritmo.
     */
    int getNClusters() const;
    void setNClusters(int value);

    QList<QString> getAlgorithmParameters() const;
    /*!
     * \brief Imposta i valori associati ai parametri dell'algoritmo a quelli indicati come parametro.
     */
    void setAlgorithmParameters(const QList<QString> &value);

    bool getStopAnalysis() const;
    void setStopAnalysis(bool value);
    /*!
     * \brief Approssima il double ricevuto in input all'intero più vicino
     */
    static int roundToInt(double num);
    /*!
     * \brief Prende la matrice in input result con numero di colonne nrows e ncols e ne ritorna la matrice trasposta
     * \param result Matrice di cui fare la trasposta
     * \param nrows Numero di righe della matrice di partenza
     * \param ncols Numero di colonne della matrice di partenza
     */
    static double** transform(double** result, const int nrows, const int ncolumns);
    /*!
     * \brief Ritorna il minimo e il massimo per side effect da tre valori
     * \param first Primo valore da esaminare
     * \param second Secondo valore da esaminare
     * \param third Terzo valore da esaminare
     * \param max Puntatore al massimo tornato per side effect
     * \param min Puntatore al minimo tornato per side effect
     */
    static void findMinMax(double first,double second,double third,double* max,double* min);
    /*!
     * \brief Metodo statico che normalizza i valori di tre array di double tra 0 e 255
     * \param redValues Array contenente i valori dei pixel corrispondenti al rosso
     * \param greenValues Array contenente i valori dei pixel corrispondenti al verde
     * \param blueValues Array contenente i valori dei pixel corrispondenti al blu
     * \param finalRed Array contenente i valori dei pixel corrispondenti al rosso normalizzati
     * \param finalGreen Array contenente i valori dei pixel corrispondenti al verde normalizzati
     * \param finalBlue Array contenente i valori dei pixel corrispondenti al blu normalizzati
     * \param mask Array contenente la maschera dell'immagine analizzata
     * \param length Numero di celle in ciascun array
     */
    static void normalize(double* redValues,double* greenValues,double* blueValues,int* finalRed,int* finalGreen,int* finalBlue,int* mask,int length);
    /*!
     * \brief Metodo per creare l'immagine in output a partire dall'array risultato di un esecuzione.
     * \param outputIterator è l'iteratore dell'immagine in output.
     * \param mask Array contenente la maschera dell'immagine analizzata
     * \param result è la matrice di double relativa al risultato.
     * \param length è il numero di pixel dell'immagine
     */
    void createImage2D(itk::ImageRegionIterator<Image2DType> outputIterator,double** result,int* mask,const int length);
    /*!
     * \brief Metodo per creare l'immagine in output a partire dall'array risultato di un esecuzione.
     * \param outputIterator è l'iteratore dell'immagine in output.
     * \param mask Array contenente la maschera dell'immagine analizzata
     * \param result è la matrice di double relativa al risultato.
     * \param length è il numero di pixel dell'immagine
     */
    void createImage3D(itk::ImageRegionIterator<Image3DType> outputIterator,double* result,int* mask,const int length);
    /*!
     * \brief Metodo che prende in input un puntatore a un'immagine maschera decodificata e ritorna un array di valori interi che la rappresentano.
     * \param mask Puntatore all'immagine maschera decodificata.
     * \param nrows Numero di righe dell'immagine di partenza.
     */
    template<typename MaskPointer,typename MaskType>
    int* getMask(MaskPointer mask,const int nrows) {

        int* maskArray = new int[nrows];
        for(int i=0;i<nrows;i++)
            maskArray[i]=255;

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
     * \brief Metodo che prende l'array rappresentante l'immagine da analizzare e la corrispondente maschera e si preoccupa di oscurare i pixel dell'immagine che sono impostati a zero nella maschera.
     * \param output Immagine da restituire con i pixel correttamente oscurati.
     * \param clusterid Array contentente l'immagine di input.
     * \param maskArray Array contenente la maschera da applicare.
     */
    template<typename ImagePointer,typename ImageType>
    void createClusteringImage(ImagePointer output,int* clusterid,int* maskArray) {
        itk::ImageRegionIterator<ImageType> iterator(output , output->GetLargestPossibleRegion());
        int index = 0;
        while(!iterator.IsAtEnd()) {
            itk::RGBPixel<unsigned char> pixel;
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
     * \brief Metodo per ottenere la quantità di ram del computer
     */
    int getTotalMemory() const;
    /*!
     * \brief Metodo per ottenere la classe del computer in base alla ram
     */
    QString getMemoryCategory() const;
    /*!
     * \brief Metodo per capire se l'analisi che si cerca di effettuare è ok
     */
    bool checkRequestedMemory(long requestedMemory) const;

signals:
    /*!
     * \brief Segnale inviato per notificare l'avventua estrazione di una feature
     * \param path Percorso alla posizione nel file system di dove è stato salvato il risultato.
     */
    void featureExtracted(QString path);
    /*!
     * \brief Segnale inviato per notificare l'avvenuta esecuzione di un algoritmo di clustering
     * \param path Percorso alla posizione nel file system di dove è stato salvato il risultato.
     */
    void algorithmExecuted(QString path);
private:
    /*!
     * \brief Nome del protocollo
     */
    QString name;
    /*!
     * \brief Breve descrizione del protocollo e delle sue funzionalità
     */
    QString description;
    /*!
     * \brief Il campo test a true indica che il protocollo è di test, a false significa che il protocollo è ufficiale
     */
    bool test;
    /*!
     * \brief Puntatore all'algoritmo di clustering definito per il protocollo.
     */
    algorithms::AbstractAlgorithm* algorithm;
    /*!
     * \brief Lista di puntatori alle features definite per il protocollo.
     */
    QList<features::AbstractFeature*> features;
    /*!
     * \brief Lista che contiene i valori dei parametri dell'algoritmo di clustering associato al protocollo.
     */
    QList<QString> algorithmParameters;
    /*!
     * \brief Numero di cluster con cui verrà eseguito l'algoritmo.
     */
    int nClusters;
    /*!
     * \brief Flag booleano che indica se le analisi devono proseguire
     */
    bool stopAnalysis;
    /*!
     * \brief Limite al numero di pixel allocabili per 2 gb di memoria
     */
    //static const int limit2GB = 51769872;
    static const int limit2GB = 1024;
    /*!
     * \brief Limite al numero di pixel allocabili per 4 gb di memoria
     */
    //static const int limit4GB = 103539744;
    static const int limit4GB = 2048;
};

}}}
#endif // ABSTRACTPROTOCOL_H
