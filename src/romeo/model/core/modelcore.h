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
    datasets::DatasetsList *getDatasetsList();
    /*!
     * \brief Ritorna la lista dei protocolli.
     */
    protocols::ProtocolsList *getProtocolsList();
    /*!
     * \brief Ritorna la lista degli algoritmi.
     */
    protocols::algorithms::AlgorithmsList *getAlgorithmsList();
    /*!
     * \brief Ritorna la lista delle feature.
     */
    protocols::features::FeaturesList *getFeaturesList();

    /*!
     * \brief Ritorna la cartella dove sono contenuti i file xml utilizzati come database.
     */
    static QDir getDataHome();


private:
    /*!
     * \brief Costruttore privato, poiché la classe ModelCore implementa il design pattern singleton
     */
    ModelCore(QObject* parent=0);

    /*!
     * \brief Metodo interno di ModelCore che si occupa di inizializzare le liste dei dati utilizzando il modulo Loader per caricare il file che contiene il database. Inoltre crea le connessioni tra i segnali di modifica e il modulo di salvataggio dei dati.
     */
    void createLists();
    /*!
     * \brief Campo dati statico che contiene il riferimento all'unica istanza del ModelCore.
     */
    static ModelCore* instance;

    /*!
     * \brief Campo dati che contiene un puntatore al modulo che gestisce il caricamento dei dati.
     */
    Loader* loader;
    /*!
     * \brief Campo dati che contiene un puntatore al modulo che gestisce il salvataggio dei dati su disco.
     */
    Writer* writer;
    /*!
     * \brief Campo dati che indica la directory dove si trovano i file informativi rispetto alla cartella da cui viene fatto partire l'applicazione.
     */
    static QDir dataHome;

signals:
    /*!
     * \brief Segnale che indica un evento anomalo che si è verificato e viene riportato un messaggio di errore tramite la stringa errorMessage.
     */
    void ioError(QString errorMessage);
public slots:
    /*!
     * \brief Slot che elimina il dataset di nome datasetName e i file su disco che ne conteneva le informazioni.
     * \param datasetName Nome del dataset da eliminare.
     */
    void deleteDataset(QString datasetName);
};


}}}
#endif // MODELCORE_H
