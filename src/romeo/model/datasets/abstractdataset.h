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
    bool associateProtocol(protocols::AbstractProtocol* protocol);
    QString getName();
    void setName(QString &value);
    QVector<QString> getSubjectList();


private:
    QString name;
    QHash<AbstractSubject*, QVector<Result*> >  results;
};
}}}
#endif // ABSTRACTDATASET_H
