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

#include <src/romeo/model/protocols/abstractprotocol.h>
#include "src/romeo/model/inputformats.h"



#ifndef ABSTRACTDATASET_H
#define ABSTRACTDATASET_H
namespace romeo {
namespace model {
namespace datasets{

/**
 * \brief La classe AbstractDataset da completare
 *
 * Descrizione dettagliata
 */

class AbstractDataset
{
public:
    AbstractDataset();
    /*!
     * \brief AbstractDataset
     * \param name
     */
    AbstractDataset(QString& name);
    /*!
     * \brief createNewSubject
     * \param n
     * \param fileSubject
     * \param mask
     */
    void createNewSubject(QString& n, QString& fileSubject, QString& mask);
    /*!
     * \brief makeSubject
     * \param n
     * \param fileSubject
     * \param mask
     * \return
     */
    AbstractSubject* makeSubject(QString& n, QString& fileSubject, QString& mask);
    /*!
     * \brief Associa un nuovo protocollo al dataset. Se il protocollo appartiene già al dataset, non viene modificato nulla e viene ritornato il valore false, altrimenti il protocollo viene aggiunto al dataset e viene ritornato true
     * \param protocol Il protocollo da aggiungere al dataset
     * \return Valore booleano che indica la riuscita dell'operazione
     */
    bool associateProtocol(protocols::AbstractProtocol* protocol);
    /*!
     * \brief Ritorna il nome del dataset
     */
    QString getName() const;
    /*!
     * \brief Modifica il nome del dataset
     */
    void setName(QString &value);
    QVector<QString> getSubjectList();


private:
    QString name;
    QHash<AbstractSubject*, QVector<Result*> >  results;
};
}}}
#endif // ABSTRACTDATASET_H
