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
    /*!
     * \brief Costruttore di Subject3D che prende in input tre parametri per il nome, il file immagine e la maschera.
     * \param name Nome del subject.
     * \param imagePath Percorso al file immagine.
     * \param maskPath Percorso al file di maschera.
     */
    Subject3D(QString &name, QString &imagePath, QString &maskPath);
    romeo::model::InputFormat getType();
};
}}}
#endif // SUBJECT3D_H
