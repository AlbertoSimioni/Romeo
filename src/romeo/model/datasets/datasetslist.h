/**
* \file datasetslist.h
* \author Matteo Pozza
* \date 2014-02-17
**
* \brief Header della classe DatasetsList del package romeo::model::datasets
*/


#ifndef DATASETSLIST_H
#define DATASETSLIST_H
#include"abstractdataset.h"
namespace romeo {
namespace model {
namespace datasets{

/**
 * \brief La classe DatasetsList contiene la lista dei dataset che il programma ha caricato e l'utente può utilizzare.
 *
 * La classe fornisce agli utilizzatori i metodi per cercare e modificare i dataset, oltre a quelli per creare un nuovo dataset o per eliminarne uno dalla lista.
 */


class DatasetsList : public QObject
{
    Q_OBJECT
public:
    /*!
     * \brief Metodo statico che ritorna l'istanza del DatasetList, in caso sia la prima volta ad essere invocato
     *  si preoccupa anche di costruire l'istanza.
     */
   static DatasetsList* getInstance(QObject *parent=0);
   /*!
    * \brief Ritorna un puntatore al dataset con il nome name.
    */
   AbstractDataset* getDataset(QString name) const;
   /*!
    * \brief Ritorna la lista di dataset attualmente caricata dall'applicazione. La lista contiene dei puntatori ai dataset su cui possono essere eseguite operazioni.
    */
   QList<AbstractDataset*> getDatasetsList() const;
   /*!
    * \brief Aggiunge un nuovo dataset del tipo indicato alla lista dei dataset.
    * \param name Nome del dataset.
    * \param datasetType Tipo del dataset.
    */
   void addDataset(QString name, InputFormat datasetType);
   /*!
    * \brief Si preoccupa di elimare dai dataset tutte le associazioni al protocollo con nome dato in input
    */
   void deleteProtocolAssociations(QString protocolName);

   ~DatasetsList();

   /*!
    * \brief Ritorna il primo dataset diverso da quello dato in input
    */
   AbstractDataset* getNextDataset(AbstractDataset* dataset);

   void deleteDataset(AbstractDataset* dataset);
   /*!
    * \brief Ritorna la lista dei nomi dei dataset attualmente presenti nella lista dei dataset.
    * \return
    */
   QList<QString> getDatasetsNames() const;
   /*!
    * \brief Aggiunge un file dataset alla lista dei dataset. Tale dataset può ora essere caricato in memoria. Se il dataset è già presente nella lista il metodo non compie modifiche.
    * \param name Nome del dataset da aggiungere.
    */
   void addDatasetFile(const QString& name);

private:
   /*!
    * \brief Costruttore privato, poiché la classe DatasetsList implementa il design pattern singleton
    */
    DatasetsList(QObject* parent=0);
    /*!
     * \brief Lista di puntatori a dataset attualmente caricati nell'applicazione.
     */
    QList<AbstractDataset*> datasets;
    /*!
     * \brief Campo dati che contiene i nomi dei dataset.
     */
    QList<QString> datasetsFiles;
    /*!
     * \brief Puntatore che si riferisce all'unica istanza di DatasetList
     */
    static DatasetsList* instance;
signals:
    /*!
     * \brief Segnale che indica una modifica avvenuta sulla lista dei dataset.
     */
    void datasetsListModified();
    /*!
     * \brief Segnale che viene inviato quando un dataset viene eliminato.
     */
    void datasetDeleted(QString datasetName);
    /*!
     * \brief Segnale che deve emettere DatasetList quando viene modificato un dataset, indicandone il nome.
     */
    void datasetModified(QString datasetName);

};
}}}
#endif // DATASETSLIST_H
