/**
* \file dataset2dt.h
* \author Matteo Pozza
* \date 2014-02-17
**
* \brief Header della classe Dataset2DT del package romeo::model::datasets
*/

#ifndef DATASET2DT_H
#define DATASET2DT_H

#include"abstractdataset.h"
namespace romeo {
namespace model {
namespace datasets{

/**
 * \brief Questa classe rappresenta un dataset che contiene subject con immagini 2D dinamiche, quindi tale classe potrà contenere associazioni a subject solamente appartenenti alla classe Subject2DT.
 *
 * Contiene le informazioni proprie dei Dataset2DT, e inoltre definisce i metodi per la modifica di tali informazioni.
 */


class Dataset2DT : public AbstractDataset
{
public:
    /*!
     * \brief Costruisce un dataset per immagini 2DT.
     * \param name Nome dato al dataset e con cui verrà salvato.
     */
    Dataset2DT(QString &name);
    /*!
     * \brief Override del metodo makeSubject di AbstractDataset che si occupa di costruire un subject di tipo Subject2DT, compatibile con i metodi di Dataset2DT. Il subject viene automaticamente aggiunto dalla superclasse AbstractDataset alla lista dei subject.
     * \param name Nome del subject da creare.
     * \param fileSubject Percorso al file immagine selezionata per il subject.
     * \param mask Percorso al file contenente la maschera compatibile con il subject indicato.
     */
    virtual AbstractSubject* makeSubject(QString& name, QString& fileSubject, QString& mask);
    /*!
     * \brief Ritorna il tipo dinamico del dataset, quindi Dataset2DT.
     */
    virtual romeo::model::InputFormat getType();
    /*!
     * \brief Ritorna il tipo dei protocolli associati al dataset, che per i Dataset2DT è "DYNAMIC".
     */
    virtual romeo::model::protocols::ProtocolType getProtocolsType();

    virtual QString checkSubject(QString &fileSubject, QString &mask);
};
}}}
#endif // DATASET2DT_H
