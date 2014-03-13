/**
* \file subject3d.h
* \author Matteo Pozza
* \date 2014-02-17
**
* \brief Header della classe Subject3D del package romeo::model::datasets
*/


#ifndef SUBJECT3D_H
#define SUBJECT3D_H

#include"abstractsubject.h"
namespace romeo {
namespace model {
namespace datasets{

/**
 * \brief Classe che rappresenta un subject con associata un'immagine 3D statica su cui sarà possibile effettuare le analisi.
 *
 * Contiene le informazioni proprie dei subject3D, e inoltre definisce i metodi per la modifica di tali informazioni.
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
