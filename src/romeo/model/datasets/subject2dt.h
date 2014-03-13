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
 * \brief Classe che rappresenta un subject con associata un'immagine 2D dinamica su cui sarà possibile effettuare le analisi.
 *
 * Contiene le informazioni proprie dei subject2DT, e inoltre definisce i metodi per la modifica di tali informazioni.
 */

class Subject2DT : public AbstractSubject
{
public:
    /*!
     * \brief Costruttore di Subject2DT che prende in input tre parametri per il nome, il file immagine e la maschera.
     * \param name Nome del subject.
     * \param imagePath Percorso al file immagine.
     * \param maskPath Percorso al file di maschera.
     */
    Subject2DT(QString &name, QString &imagePath, QString &maskPath);
    romeo::model::InputFormat getType();
};
}}}
#endif // SUBJECT2DT_H
