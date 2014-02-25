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
 * \brief La classe Dataset3D da completare
 *
 * Descrizione dettagliata
 */



class Dataset3D : public AbstractDataset
{
public:
    Dataset3D(QString &name);
    virtual AbstractSubject* makeSubject(QString& name, QString& fileSubject, QString& mask);
};
}}}
#endif // DATASET3D_H
