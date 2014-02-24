/**
* \file dynamicprotocol.h
* \author Matteo Pozza
* \date 2014-02-17
**
* \brief Header della classe DynamicProtocol del package romeo::model::protocols
*/


#ifndef PROTOCOLSLIST_H
#define PROTOCOLSLIST_H

#include <QObject>

#include "abstractprotocol.h"

namespace romeo {
namespace model {
namespace protocols{


/**
 * \brief La classe ProtocolsList
 *
 * Descrizione dettagliata
 */
class ProtocolsList : public QObject
{
    Q_OBJECT
public:
    /**
      * \brief Il distruttore della classe ProtocolsList rimuove dallo heap i riferimenti ai protocolli
    */
    //~ProtocolsList();
    /*!
    * \brief Metodo statico che ritorna l'istanza di AlgorithmList, in caso sia la prima volta ad essere invocato
    *  si preoccupa anche di costruire l'istanza.
    */
    static ProtocolsList* getInstance(QObject* parent);
    /*!
     * \brief Inserisce nella lista dei protocolli un nuovo protocollo definito dai parametri passati
     * \param name definisce il nome del nuovo protocollo che si vuole creare
     * \param algorithm è il nome dell'algoritmo da inserire
     * \param features è il vettore contenente i nomi delle feature da inserire
     * \param type indica se è un protocollo statico o dinamico, di default STATICO
     */
    void addProtocol(QString &name,QString desc, QString &algorithm, QList<QString> &features, ProtocolType type =  STATIC);

    void addProtocol(QString nomeP, QString desc, algorithms::AbstractAlgorithm* alg, QList<features::AbstractFeature*>& feat, ProtocolType type);
    /*!
     * \brief Ritorna il riferimento al protocollo con nome uguale al parametro name
     * \param name Nome dell'algoritmo da ritornare
     * \return Riferimento al protocollo
     */
    AbstractProtocol* getProtocol(QString name);

    QList<protocols::AbstractProtocol *> getProtocolsList() const;

signals:
    /*!
     * \brief Segnale che indica che è avvenuta una modifica nella lista dei protocolli
     */
    void protocolsListModified();


private:
    /**
     * \brief ProtocolsList costruisce la lista di protocolli
     */
    explicit ProtocolsList(QObject *parent = 0);
    /*!
     * \brief Il vettore contiene la lista dei protocolli creati dall'utente
     */
    QList<protocols::AbstractProtocol*> protocolsList;
    static ProtocolsList* instance;
};
}}}

#endif // PROTOCOLSLIST_H
