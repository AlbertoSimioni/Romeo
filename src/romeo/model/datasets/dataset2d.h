/**
* \file dataset2d.h
* \author Matteo Pozza
* \date 2014-02-17
**
* \brief Header della classe Dataset2D del package romeo::model::datasets
*/

#ifndef DATASET2D_H
#define DATASET2D_H

#include"abstractdataset.h"
namespace romeo {
namespace model {
namespace datasets{

/**
 * \brief La classe Dataset2D da completare
 *
 * Descrizione dettagliata
 */


class Dataset2D : public AbstractDataset
{
public:
    /*!
     * \brief Costruisce un dataset per immagini 2D.
     * \param name Nome dato al dataset e con cui verrà salvato.
     */
    Dataset2D(QString& name);
    /*!
     * \brief Override del metodo makeSubject di AbstractDataset che si occupa di costruire un subject di tipo Subject2D, compatibile con i metodi di Dataset2D. Il subject viene automaticamente aggiunto dalla superclasse AbstractDataset alla lista dei subject.
     * \param name Nome del subject da creare.
     * \param fileSubject Percorso al file immagine selezionata per il subject.
     * \param mask Percorso al file contenente la maschera compatibile con il subject indicato.
     */
    virtual AbstractSubject* makeSubject(QString& name, QString& fileSubject, QString& mask);
    /*!
     * \brief Ritorna il tipo dinamico del dataset, quindi Dataset2D.
     */
    virtual romeo::model::InputFormat getType();
    /*!
     * \brief Ritorna il tipo dei protocolli associati al dataset, che per i Dataset2D è "STATIC".
     */
    virtual romeo::model::protocols::ProtocolType getProtocolsType();
};
}}}
#endif // DATASET2D_H
