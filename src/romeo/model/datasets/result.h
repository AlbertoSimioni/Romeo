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
    Result(QDate ed, QString pn,QString rp, bool fr, QString fn = QString());
    /*!
     * \brief Ritorna true se il risultato è stato ottenuto
     */
    bool getFeatureResult() const;
    QString getFeatureName() const;
    QString getProtocolName() const;
    QDate getExecutionDate() const;
    QString getResultPath() const;
};

}}}
#endif // RESULT_H
