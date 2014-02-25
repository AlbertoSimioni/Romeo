/**
* \file subject3d.h
* \author Matteo Pozza
* \date 2014-02-17
**
* \brief Header della classe Subject3DT del package romeo::model::datasets
*/


#ifndef SUBJECT3D_H
#define SUBJECT3D_H

#include"abstractsubject.h"
namespace romeo {
namespace model {
namespace datasets{

/**
 * \brief La classe Subject3D da completare
 *
 * Descrizione dettagliata
 */

class Subject3D : public AbstractSubject
{
public:
    Subject3D(QString &name, QString &imagePath, QString &maskPath);
    QString getType();
};
}}}
#endif // SUBJECT3D_H
