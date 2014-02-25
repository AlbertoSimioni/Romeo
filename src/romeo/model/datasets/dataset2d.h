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
    Dataset2D(QString& name);
    virtual AbstractSubject* makeSubject(QString& name, QString& fileSubject, QString& mask);
    virtual romeo::model::InputFormat getType();
};
}}}
#endif // DATASET2D_H
