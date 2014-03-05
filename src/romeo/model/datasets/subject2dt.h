/**
* \file subject2dt.h
* \author Matteo Pozza
* \date 2014-02-17
**
* \brief Header della classe Subject2DT del package romeo::model::datasets
*/

#ifndef SUBJECT2DT_H
#define SUBJECT2DT_H

#include"abstractsubject.h"
namespace romeo {
namespace model {
namespace datasets{

/**
 * \brief La classe Subject2DT da completare
 *
 * Descrizione dettagliata
 */

class Subject2DT : public AbstractSubject
{
public:
    Subject2DT(QString &name, QString &imagePath, QString &maskPath);
    romeo::model::InputFormat getType();
};
}}}
#endif // SUBJECT2DT_H
