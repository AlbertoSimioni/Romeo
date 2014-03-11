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
#include "algorithms/abstractalgorithm.h"
#include "features/abstractfeature.h"
#include "../datasets/abstractsubject.h"

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

    virtual ~AbstractProtocol();

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
};

}}}
#endif // ABSTRACTPROTOCOL_H
