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

    void addProtocol(QString nomeP, QString desc, algorithms::AbstractAlgorithm* alg, QList<features::AbstractFeature*>& feat, ProtocolType type, int window=1, int distanceGLCM=3);
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
