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
     * @brief ProtocolsList costruisce la lista di protocolli
     */
    explicit ProtocolsList(QObject *parent = 0);
    /**
      * \brief Il distruttore della classe ProtocolsList rimuove dallo heap i riferimenti ai protocolli
    */
    //~ProtocolsList();
    /*!
     * \brief Inserisce nella lista dei protocolli un nuovo protocollo definito dai parametri passati
     * \param nome definisce il nome del nuovo protocollo che si vuole creare
     * \param algorithm è il nome dell'algoritmo da inserire
     * \param features è il vettore contenente i nomi delle feature da inserire
     * \param tipo indica se è un protocollo statico o dinamico, di default STATICO
     */
    void addProtocol(QString &nome, QString &algorithm, QList<QString> &features, AbstractProtocol::TipoProtocollo tipo=AbstractProtocol::STATICO);

    /*!
     * \brief Ritorna il riferimento al protocollo con nome uguale al parametro name
     * \param name Nome dell'algoritmo da ritornare
     * \return Riferimento al protocollo
     */
    AbstractProtocol* getProtocol(QString name);

signals:
    /*!
     * \brief Segnale che indica che è avvenuta una modifica nella lista dei protocolli
     */
    void protocolsListModified();

private:
    /*!
     * \brief Il vettore contiene la lista dei protocolli creati dall'utente
     */
    QList<protocols::AbstractProtocol*> protocolsList;
};
}}}

#endif // PROTOCOLSLIST_H
