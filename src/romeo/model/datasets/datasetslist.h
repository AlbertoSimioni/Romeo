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
 * \brief La classe DatasetsList da completare
 *
 * Descrizione dettagliata
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

   QList<QString> getDatasetsFiles() const;
   void addDatasetFile(const QString& name);

private:
   /*!
    * \brief Costruttore privato, poiché la classe Loader implementa il design pattern singleton
    */
    DatasetsList(QObject* parent=0);
    /*!
     * \brief Lista di puntatori a dataset attualmente caricati nell'applicazione
     */
    QList<AbstractDataset*> datasets;
    /*!
     * \brief Campo dati che mappa i nomi dei file di dataset con i rispettivi file
     */
    QList<QString> datasetsFiles;
    /*!
     * \brief Puntatore che si riferisce all'unica istanza di DatasetList
     */
    static DatasetsList* instance;
signals:
    /*!
     * \brief Segnale che indica una modifica avvenuta sulla lista dei dataset
     */
    void datasetsListModified();

};
}}}
#endif // DATASETSLIST_H
