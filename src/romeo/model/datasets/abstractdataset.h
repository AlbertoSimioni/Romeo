/**
* \file abstractdataset.h
* \author Matteo Pozza
* \date 2014-02-17
**
* \brief Header della classe AbstractDataset del package romeo::model::datasets
*/

#include "result.h"

#include <QHash>
#include <QString>
#include <QFuture>
#include <src/romeo/model/protocols/abstractprotocol.h>
#include "src/romeo/model/inputformats.h"
#include <src/romeo/model/protocols/abstractprotocol.h>
#include <src/romeo/model/protocols/abstractprotocol.h>


#ifndef ABSTRACTDATASET_H
#define ABSTRACTDATASET_H
namespace romeo {
namespace model {
namespace datasets{

/**
 * \brief Classe astratta che rappresenta un dataset contente più subject e protocolli. Questa classe è stata progettata seguendo il design pattern Factory Method, in particolare la classe mette a disposizione un metodo per creare un nuovo subject e delega alle sottoclassi l'effettiva istanziazione di tale subject.
 *
 * Mette a disposizione i metodi per inserire nuove associazioni a subject e protocolli. Contiene le informazioni necessarie e comuni a tutti i tipi dataset e mette a disposizione i metodi per reperire e modificare tali informazioni.
 *
 * Descrizione dettagliata
 */

class AbstractDataset: public QObject
{
    Q_OBJECT
public:

    /*!
     * \brief Costruisce un nuovo dataset con il nome indicato
     * \param name Nome con cui costruire in nuovo dataset
     */
    AbstractDataset(QString& name);
    /*!
      * \brief Distruttore di AbstractDataset, si preoccupa di non lasciare memoria garbage nel sistema e quindi di fare una distruzione profonda dei puntatori che ha come campi dato.
      */
    virtual ~AbstractDataset();
    /*!
     * \brief Metodo per la creazione di un nuovo subject che prende in input le informazioni necessarie alla creazione e richiama il metodo virtuale makeSubject() che viene ridefinito dalle sottoclassi e permette di creare i vari tipi di subjects.
     * \param n Nome del subject da creare e aggiungere al dataset
     * \param fileSubject Percorso del filesystem al file immagine del subject
     * \param mask Percorso alla mask del subject
     */
    void createNewSubject(QString& name, QString& fileSubject, QString& mask);
    /*!
     * \brief Metodo virtuale puro che deve essere ridefinito dalle sottoclassi in base al tipo di subject che si vuole costruire. Il metodo è chiamato da createNewSubject e costruisce un nuovo subject dello stesso tipo del tipo del dataset che ne ha richiesto la costruzione (2D per i dataset 2D, 3D per quelli 3D ecc..)
     * \param n Nome del subject da creare
     * \param fileSubject Percorso all'immagine associata al subject
     * \param mask Percorso alla maschera associata al subject
     * \return Ritorna un puntatore al nuovo subject appena creato
     */
    virtual AbstractSubject* makeSubject(QString& n, QString& fileSubject, QString& mask) = 0;
    /*!
     * \brief Associa un nuovo protocollo al dataset. Se il protocollo appartiene già al dataset, non viene modificato nulla e viene ritornato il valore false, altrimenti il protocollo viene aggiunto al dataset e viene ritornato true
     * \param protocol Il protocollo da aggiungere al dataset
     */
    void associateProtocol(protocols::AbstractProtocol* protocol);
    /*!
     * \brief Ritorna il nome del dataset
     */
    QString getName() const;
    /*!
     * \brief Modifica il nome del dataset
     */
    void setName(QString &value);
    /*!
     * \brief Ritorna i subject collegati al dataset sotto forma di lista di QString
     */
    QList<AbstractSubject*> getSubjectList()const;

    /*!
     * \brief Se è presente un protocollo con nome uguale a quello in input, lo rimuove dalla lista dei protocolli associati
     */
    void removeProtocolAssociation(QString protocolName);
    /*!
     * \brief Ritorna la lista di protocolli associati al dataset
     */
    QList<protocols::AbstractProtocol*> getAssociatedProtocolsList();

    /*!
     * \brief Ritorna il tipo del dataset
     */
    virtual romeo::model::InputFormat getType() = 0;
    QString getTypeString();
    /*!
     * \brief Ritorna il tipo di protocolli che è possibile associare al dataset
     */
    virtual romeo::model::protocols::ProtocolType getProtocolsType() = 0;
    /*!
     * \brief Aggiunge un risultato al protocollo identificato da protocol per il dataset in uso.
     * \param protocol Il protocollo per il quale è presente il risultato da aggiungere.
     * \param result Il risultato che deve essere aggiunto.
     */
    void addResult(romeo::model::protocols::AbstractProtocol* protocol,Result* result);


    /*!
     * \brief Ritorna una lista che rappresenta i percorsi ai risultati per il protocollo di nome protocol
     */
    QStringList getProtocolResults(const QString& protocol) const;
    QList<Result*> getResultsList(const QString& protocol) const;

    /*!
     * \brief getResultPath
     * \param protocol
     * \param resultDate
     * \return
     */
    QString getResultPath(QString protocol,QString resultDate);
    /*!
     * \brief Ritorna un puntatore al protocollo di nome protocolName, prendendolo dalla lista dei protocolli assiociati al dataset. Se il protocollo non è presente viene ritornato un puntatore nullo.
     */
    protocols::AbstractProtocol* getProtocol(const QString& protocolName)const;
    /*!
     * \brief Ritorna i protocolli associati al dataset sotto forma di lista cotenente i nomi dei protocolli.
     */
    QList<protocols::AbstractProtocol*> getProtocolList() const;
    /*!
     * \brief Ritorna un puntatore al subject presente nel dataset con nome subjectName.
     */
    AbstractSubject* getSubject(const QString& subjectName) const;
    /*!
     * \brief Aggiunge al protocollo protocolName un percorso riguardante un risultato ottenuto eseguento tale protocollo.
     */
    void addResult(QString protocolName, QString resultPath);
    /*!
     * \brief Elimina il subject di nome subjectName contenuto del dataset, rimuovendolo inoltre dalla lista dei subject.
     */
    void deleteSubject(const QString& subjectName);

    /*!
     * \brief Metodo che avvia un nuovo thread in cui esegue le analisi sui subjects con nome dato in input applicando il protocollo dato in input
     * \param protocol Nome del protocollo con cui si vuole procedere all'esecuzione.
     * \param subjects Lista dei subject che devono essere processati.
     * \param resultsPath Percorso alla cartella dove salvare i risultati.
     * \param saveFeatures Parametro booleano, quando a true indica che i risultati delle features vanno salvati.
     * \param exportFormat Tipo di esportazione dei risultati.
     */
    void executeAnalysis(QString protocol,QList<QString> subjects,QString resultsPath,bool saveFeatures,QString exportFormat);
    /*!
     * \brief Metodo che interrompe le analisi andando a cambiare il flag booleano per l'interruzione
     */
    void abortAnalysis();

protected:

    /*!
     * \brief Metodo che controlla la validità del subject che si vuole inserire
     * \param fileSubject Percorso all'immagine da analizzare
     * \param mask Percorso alla immagine da usare come maschera
     */
    virtual QString checkSubject(QString& fileSubject, QString& mask) = 0;

signals:

    /*!
     * \brief Segnale che indica l'inserimento di un nuovo subject nel dataset corrente.
     * \param subjectName Il nome del subject inserito.
     * \param dataPath Il percorso al file di immagine del subject.
     * \param maskPath Il percorso al file contenente la maschera del subject.
     */
    void addedSubject(QString subjectName, QString dataPath, QString maskPath);
    /*!
     * \brief Segnale che indica la rimozione di un subject.
     * \param subjectName Nome del subject rimosso dal dasatet attuale.
     */
    void removedSubject(QString subjectName);
    /*!
     * \brief Segnale che viene inviato quando viene fatta una modifica alla lista dei protocolli associati al dataset.
     */
    void protocolsModified();
    /*!
     * \brief Segnale che indica la presenza di nuovi risultati per il dataset corrente.
     */
    void newResults();
    /*!
     * \brief Segnale che indica una modifica avvenuta sul dataset di nome datasetName
     */
    void modified(QString datasetName);
    /*!
     * \brief Segnale emesso quando il protocollo ha terminato di calcolare una feature.
     */
    void featureExtracted(QString pathToResult);
    /*!
     * \brief Segnale emesso quando il protocollo ha terminato di eseguire l'algoritmo di clustering
     */
    void algorithmExecuted(QString pathToResult);

    /*!
     * \brief Segnale emesso quando il dataset ha finito eseguire le analisi
     */
    void analysisFinished();

    /*!
     * \brief Segnale emesso nel caso in cui i controlli sulla validità del subject che si vuole inserire falliscano
     */
    void invalidSubject(QString messageError);

    /*!
     * \brief Segnale emesso nel caso in cui i controlli sulla validità del subject che si vuole inserire falliscano
     */
    void analysisProblem(QString messageError);


private:
    /*!
     * \brief Nome del dataset.
     */
    QString name;
    /*!
     * \brief Una hashmap che contiene i protocolli collegati al dataset e i risultati a loro legati.
     */
    QHash<protocols::AbstractProtocol*, QList<Result*> >  protocols;
    /*!
     * \brief Lista dei subject contenuti nel dataset.
     */
    QList<AbstractSubject*> subjects;
    /*!
     * \brief flag booleano che indica se le analisi sono da proseguire
     */
    bool stopAnalysis;

    /*!
     * \brief Riferimento al protocollo in esecuzione
     */
    protocols::AbstractProtocol* currentProtocol;


};
}}}
#endif // ABSTRACTDATASET_H
