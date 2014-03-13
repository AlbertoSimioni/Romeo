/**
* \file subject3dt.h
* \author Matteo Pozza
* \date 2014-02-17
**
* \brief Header della classe Subject3DT del package romeo::model::datasets
*/

#ifndef SUBJECT3DT_H
#define SUBJECT3DT_H

#include"abstractsubject.h"
namespace romeo {
namespace model {
namespace datasets{

/**
 * \brief Classe che rappresenta un subject con associata un'immagine 3D dinamica su cui sarà possibile effettuare le analisi.
 *
 * Contiene le informazioni proprie dei subject3DT, e inoltre definisce i metodi per la modifica di tali informazioni.
 */

class Subject3DT : public AbstractSubject
{
public:
    /*!
     * \brief Costruttore di Subject3DT che prende in input tre parametri per il nome, il file immagine e la maschera.
     * \param name Nome del subject.
     * \param imagePath Percorso al file immagine.
     * \param maskPath Percorso al file di maschera.
     */
    Subject3DT(QString &name, QString &imagePath, QString &maskPath);
    /*!
     * \brief Ritorna il tipo del subject
     */
    virtual romeo::model::InputFormat getType();
};
}}}
#endif // SUBJECT3DT_H
