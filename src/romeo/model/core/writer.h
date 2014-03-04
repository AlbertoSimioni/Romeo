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
 * \brief Classe che si preoccupa di salvare le informazioni sullo stato del Model permanentemente.
 *
 * Per il salvataggio delle informazioni vengono utilizzati dei file XML, usufruendo delle classi di Qt XML. In particolare questa classe è stata progettata cercando di renderla indipendente dalla classe ModelCore contenente le informazioni del Model. Inoltre la classe realizza il design pattern Singleton, poiché l'entità rappresentata non deve avere più di un'istanza.
 * Mette a disposizione i metodi per salvare permanentemente su file XML le informazioni che varranno passate in input ai vari metodi.
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
    /*!
     * \brief Metodo che si occupa di salvare le informazioni dei subject un dataset su disco.
     * \param dataset Il dataset da salvare
     * \param writer Lo streamWriter che andrà a salvare le informazioni.
     */
    static void writeDatasetSubjects(const datasets::AbstractDataset* dataset, QXmlStreamWriter& writer);
    /*!
     * \brief Metodo che salva le informazioni dei protocolli associati a un subject su disco.
     * \param dataset Il dataset da cui estrarre le informazioni.
     * \param writer Lo stream che va a salva le informazioni.
     */
    static void writeDatasetProtocols(const datasets::AbstractDataset* dataset, QXmlStreamWriter& writer);
    /*!
     * \brief Metodo che salva le informazioni delle feature associate a un protocollo.
     * \param featureNames I nomi delle feature da salvare.
     * \param writer Lo stream di scrittura che salva le informazioni sul buffer.
     */
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
     * \brief Slot pubblico che viene chiamato ogni qualvolta sia stato effettuato un cambiamento nei datasets, questa funzione si assicura di aggiornare il file di database che contiene i dataset per mantenerlo consistente con i dati del programma.
     */
    bool saveDatasetsList();
    /*!
     * \brief Slot pubblico che viene chiamato ogni qualvolta sia stato effettuato un cambiamento in un dataset, questa funzione si assicura di aggiornare il file relativo a tale dataset per mantenerlo consistente con i dati del programma.
     */
    bool saveDataset(const QString& datasetName);
};


}}}

#endif // WRITER_H
