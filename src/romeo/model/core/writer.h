/**
* \file writer.h
* \author Matteo Pozza
* \date 2014-02-17
**
* \brief Header della classe Writer del package romeo::model::core
*/

#include <QDir>
#include <QXmlStreamWriter>
#include <src/romeo/model/datasets/abstractdataset.h>

#ifndef WRITER_H
#define WRITER_H

namespace romeo {
namespace model {
namespace core{

/**
 * \brief La classe Writer da completare
 *
 * Descrizione dettagliata
 */

class Writer: public QObject
{
    Q_OBJECT
public:
    /*!
     * \brief Metodo statico che ritorna l'istanza del Writer, in caso sia la prima volta ad essere invocato
     *  si preoccupa anche di costruire l'istanza.
     */
    static Writer* getInstance(QObject* parent=0);


private:
    /*!
     * \brief Costruttore privato, poiché la classe Writer implementa il design pattern singleton
     */
    Writer(QObject *parent=0);

    /*!
     * \brief Campo dati statico che contiene il riferimento all'unica istanza del Writer
     */
    static Writer* instance;
    static void writeDatasetSubjects(const datasets::AbstractDataset* dataset, QXmlStreamWriter& writer);
    static void writeDatasetProtocols(const datasets::AbstractDataset* dataset, QXmlStreamWriter& writer);
    static void writeProtocolFeatures(QStringList featureNames, QXmlStreamWriter& writer);

public slots:

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
    /*!
     * \brief Slot pubblico che viene chiamato ogni qualvolta sia stato effettuato un cambiamento nei datasets, questa funzione si assicura di aggiornare il file di database che contiene i dataset per mantenerlo consistente con i dati del programma.
     */
    bool saveDatasetsList();

    bool saveDataset(const QString& datasetName, const QString& datasetFile);
};


}}}

#endif // WRITER_H
