/**
* \file dataset3d.h
* \author Matteo Pozza
* \date 2014-02-17
**
* \brief Header della classe Dataset3D del package romeo::model::datasets
*/

#ifndef DATASET3D_H
#define DATASET3D_H

#include"abstractdataset.h"
namespace romeo {
namespace model {
namespace datasets{

/**
 * \brief Questa classe rappresenta un dataset che contiene subject con immagini 3D statiche, quindi tale classe potrà contenere associazioni a subject solamente appartenenti alla classe Subject3D.
 *
 * Contiene le informazioni proprie dei Dataset3D, e inoltre definisce i metodi per la modifica di tali informazioni
 */

class Dataset3D : public AbstractDataset
{
public:
    /*!
     * \brief Costruisce un dataset per immagini 3D.
     * \param name Nome dato al dataset e con cui verrà salvato.
     */
    Dataset3D(QString &name);
    /*!
     * \brief Override del metodo makeSubject di AbstractDataset che si occupa di costruire un subject di tipo Subject3D, compatibile con i metodi di Dataset3D. Il subject viene automaticamente aggiunto dalla superclasse AbstractDataset alla lista dei subject.
     * \param name Nome del subject da creare.
     * \param fileSubject Percorso al file immagine selezionata per il subject.
     * \param mask Percorso al file contenente la maschera compatibile con il subject indicato.
     */
    virtual AbstractSubject* makeSubject(QString& name, QString& fileSubject, QString& mask);
    /*!
     * \brief Ritorna il tipo dinamico del dataset, quindi Dataset3D.
     */
    virtual romeo::model::InputFormat getType();
    /*!
     * \brief Controlla la consistenza del subject rispetto alle caratteristiche del dataset
     * \param fileSubject Percorso all'immagine da analizzare
     * \param mask Percorso alla maschera dell'immagine da analizzare
     */
    virtual romeo::model::protocols::ProtocolType getProtocolsType();

    virtual QString checkSubject(QString &fileSubject, QString &mask);
};
}}}
#endif // DATASET3D_H
