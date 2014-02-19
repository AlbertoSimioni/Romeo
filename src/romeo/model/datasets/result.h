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
    /*!
     * \brief Data di esecuzione dell'algoritmo
     */
    QDate executionDate;
    /*!
     * \brief Nome del protocollo con il quale è stato ottenuto il risultato
     */
    QString protocolName;
    /*!
     * \brief Stringa contenente il percorso nel file system dove è presente il l'immagine contenente il risultato
     */
    QString resultPath;
    /*!
     * \brief Flag booleano che indica se il risultato è stato ottenuto solamente tramite l'estrazione di una feature
     */
    bool featureResult;
    /*!
     * \brief Se il flag featureResult è true, tale campo contiene il nome della feature con cui è stato ottenuto il risultato
     */
    QString featureName;

public:
    //Result(QDate ed, QString pn,QString rp, bool fr, QString fn = QString());
    /*!
     * \brief Ritorna true se il risultato è stato ottenuto
     */
    bool getFeatureResult() const;
    /*!
     * \brief Ritorna una stringa con il nome della feature con cui il risultato è stato ottenuto.
     * Se il risultato è stato ottenuto anche mediante un algoritmo di clustering ritorna una stringa vuota
     */
    QString getFeatureName() const;
    /*!
     * \brief Ritorna il nome del protocollo con cui è stato ottenuto il risultato
     */
    QString getProtocolName() const;
    /*!
     * \brief Ritorna la data in cui è stato creato il risultato
     */
    QDate getExecutionDate() const;
    /*!
     * \brief Ritorna il percorso relativo nel file system dove è presente l'immagine contenente il risultato
     */
    QString getResultPath() const;
};

}}}
#endif // RESULT_H
