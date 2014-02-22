/**
* \file modelcore.h
* \author Matteo Pozza
* \date 2014-02-17
**
* \brief Header della classe ModelCore del package romeo::model::core
*/

#include "loader.h"
#include "writer.h"

#include <src/romeo/model/imageIO/handlerio.h>
#include <src/romeo/model/imageIO/handlerio.h>
#include <src/romeo/model/datasets/datasetslist.h>
#include <src/romeo/model/protocols/protocolslist.h>
#include <src/romeo/model/protocols/algorithms/algorithmslist.h>
#include <src/romeo/model/protocols/features/featureslist.h>
#include <QDir>
#include <QHash>
#ifndef MODELCORE_H
#define MODELCORE_H

namespace romeo {
namespace model {
namespace core{
/**
 * \brief La classe ModelCore da completare
 *
 * Descrizione dettagliata
 */
class ModelCore : QObject
{
    Q_OBJECT
public:
    /*!
     * \brief Metodo statico che ritorna l'istanza del ModelCore, in caso sia la prima volta ad essere invocato
     *  si preoccupa anche di costruire l'istanza.
     * \param parent Indica al ModelCore il suo QObject parent con cui viene costruito.
     */
    static ModelCore* getInstance(QObject* parent=0);
    /*!
     * \brief Ritorna la lista dei dataset.
     */
    datasets::DatasetsList *getDatasetsList() const;
    /*!
     * \brief Ritorna la lista dei protocolli.
     */
    protocols::ProtocolsList *getProtocolsList() const;
    /*!
     * \brief Ritorna la lista degli algoritmi.
     */
    protocols::algorithms::AlgorithmsList *getAlgorithmsList() const;
    /*!
     * \brief Ritorna la lista delle feature.
     */
    protocols::features::FeaturesList *getFeaturesList() const;

    /* Metodi per ricavare i vari dati e che vengono usati da loader e writer per processare i file xml
    */
    datasets::AbstractDataset* getDataset() const;
    datasets::AbstractSubject* getSubject() const;
    protocols::AbstractProtocol* getProtocol(QString& protocol) const;
    protocols::features::AbstractFeature* getFeature(QString& feature) const;
    protocols::algorithms::AbstractAlgorithm* getAlgorithm(QString& alg) const;


private:
    /*!
     * \brief Costruttore privato, poiché la classe ModelCore implementa il design pattern singleton
     */
    ModelCore(QObject* parent=0);


    bool loadData(QDir& file);

    /*!
     * \brief Metodo interno di ModelCore che si occupa di inizializzare le liste dei dati utilizzando il modulo Loader per caricare il file che contiene il database. Inoltre crea le connessioni tra i segnali di modifica e il modulo di salvataggio dei dati.
     */
    void createLists();


    /*!
     * \brief Campo dati statico che contiene il riferimento all'unica istanza del controller.
     */
    static ModelCore* instance;
    /*!
     * \brief Campo privato che contiene la posizione nel file system del file che conntiene i dati dell'applicazione.
     */
    QDir databaseFile;
    /*!
     * \brief Contiene la lista dei percorsi ai file che hanno le informazioni sui dataset in uso.
     */
    QHash<QString, QDir> datasetsFiles;
    /*!
     * \brief Puntatore alla lista dei dataset.
     */
    datasets::DatasetsList* datasetsList;
    /*!
     * \brief Puntatore alla lista dei protocolli.
     */
    protocols::ProtocolsList* protocolsList;
    /*!
     * \brief Puntatore alla lista degli algoritmi.
     */
    protocols::algorithms::AlgorithmsList* algorithmsList;
    /*!
     * \brief Puntatore alla lista delle features.
     */
    protocols::features::FeaturesList* featuresList;

    /*!
     * \brief Campo dati che contiene un puntatore al modulo che gestisce il caricamento dei dati
     */
    Loader* loader;
    /*!
     * \brief Campo dati che contiene un puntatore al modulo che gestisce il salvataggio dei dati su disco
     */
    Writer* writer;

public slots:
    /*!
     * \brief Slot pubblico che viene chiamato ogni qualvolta sia stato effettuato un cambiamento nei datasets, questa funzione si assicura di aggiornare il file di database che contiene i dataset per mantenerlo consistente con i dati del programma.
     */
    bool saveDatasetsList();
    /*!
     * \brief Slot pubblico che viene chiamato ogni qualvolta sia stato effettuato un cambiamento nei protocolli, questa funzione si assicura di aggiornare il file di database che contiene i protocolli per mantenerlo consistente con i dati del programma.
     */
    bool saveProtocolsList();

    /*!
     * \brief Slot pubblico che viene chiamato ogni qualvolta sia stato effettuato un cambiamento negli algoritmi, questa funzione si assicura di aggiornare il file di database che contiene gli algoritmi per mantenerlo consistente con i dati del programma.
     */
    bool saveAlgorithmsList();
    /*!
     * \brief Slot pubblico che viene chiamato ogni qualvolta sia stato effettuato un cambiamento nelle feature, questa funzione si assicura di aggiornare il file di database che contiene le feature per mantenerlo consistente con i dati del programma.
     */
    bool saveFeaturesList();
    /*!
     * \brief Slot pubblico che viene chiamato ogni qualvolta sia stato effettuato un cambiamento in un dataset, questa funzione si assicura di aggiornare il file relativo a tale dataset per mantenerlo consistente con i dati del programma.
     */
    bool saveDataset(QString& datasetName);
};


}}}
#endif // MODELCORE_H
