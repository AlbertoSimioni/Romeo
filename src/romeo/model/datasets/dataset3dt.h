/**
* \file dataset3dt.h
* \author Matteo Pozza
* \date 2014-02-17
**
* \brief Header della classe Dataset3DT del package romeo::model::datasets
*/


#ifndef DATASET3DT_H
#define DATASET3DT_H

#include"abstractdataset.h"
namespace romeo {
namespace model {
namespace datasets{

/**
 * \brief La classe Dataset3D da completare
 *
 * Descrizione dettagliata
 */

class Dataset3DT : public AbstractDataset
{
public:
    Dataset3DT(QString &name);
    virtual AbstractSubject* makeSubject(QString& name, QString& fileSubject, QString& mask);
};
}}}
#endif // DATASET3DT_H
