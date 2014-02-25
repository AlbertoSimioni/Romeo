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
 * \brief La classe Dataset2DT da completare
 *
 * Descrizione dettagliata
 */


class Dataset2DT : public AbstractDataset
{
public:
    Dataset2DT(QString &name);
    virtual AbstractSubject* makeSubject(QString& name, QString& fileSubject, QString& mask);
    virtual romeo::model::InputFormat getType();
};
}}}
#endif // DATASET2DT_H
