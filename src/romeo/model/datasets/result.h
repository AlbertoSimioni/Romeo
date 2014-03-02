/**
* \file result.h
* \author Matteo Pozza
* \date 2014-02-17
**
* \brief Header della classe Result del package romeo::model::datasets
*/


#ifndef RESULT_H
#define RESULT_H

#include<QDate>
#include<QString>
namespace romeo {
namespace model {
namespace datasets{

/**
 * \brief La classe Result da completare
 *
 * Descrizione dettagliata
 */

class Result
{
public:
    Result(QDate execDate,QString pathToResult);
    /*!
     * \brief Costruisce un nuovo oggetto di tipo risultato indicando il percorso dove sono salvati i risultati delle esecuzioni.
     */
    Result(QString pathToResult);
    /*!
     * \brief Ritorna la data in cui è stato creato il risultato
     */
    QDate getExecutionDate() const;
    /*!
     * \brief Ritorna il percorso relativo nel file system dove è presente l'immagine contenente il risultato
     */
    QString getResultPath() const;

private:
    /*!
     * \brief Data di esecuzione dell'algoritmo
     */
    QDate executionDate;

    /*!
     * \brief Stringa contenente il percorso nel file system dove è presente il l'immagine contenente il risultato
     */
    QString resultPath;
};

}}}
#endif // RESULT_H
