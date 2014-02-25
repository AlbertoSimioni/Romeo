/**
* \file subject2d.h
* \author Matteo Pozza
* \date 2014-02-17
**
* \brief Header della classe Subject2D del package romeo::model::datasets
*/


#ifndef SUBJECT2D_H
#define SUBJECT2D_H

#include"abstractsubject.h"
namespace romeo {
namespace model {
namespace datasets{

/**
 * \brief La classe Subject2D da completare
 *
 * Descrizione dettagliata
 */


class Subject2D : public AbstractSubject
{
public:
    Subject2D(QString& name, QString& imagePath, QString& maskPath);
    virtual QString getType();
};
}}}
#endif // SUBJECT2D_H
