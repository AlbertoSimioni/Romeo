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
 * \brief Classe che rappresenta un subject con associata un'immagine 2D statica su cui sarà possibile effettuare le analisi.
 *
 * Contiene le informazioni proprie dei subject2D, e inoltre definisce i metodi per la modifica di tali informazioni.
 */

class Subject2D : public AbstractSubject
{
public:
    /*!
     * \brief Costruttore di Subject2D che prende in input tre parametri per il nome, il file immagine e la maschera.
     * \param name Nome del subject.
     * \param imagePath Percorso al file immagine.
     * \param maskPath Percorso al file di maschera.
     */
    Subject2D(QString& name, QString& imagePath, QString& maskPath);

    /*!
     * \brief Ritorna il tipo dinamico del subject.
     */
    virtual InputFormat getType();
};
}}}
#endif // SUBJECT2D_H
