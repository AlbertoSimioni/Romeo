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
 * \brief La classe ProtocolsList da completare
 *
 * Descrizione dettagliata
 */
class ProtocolsList : public QObject
{
    Q_OBJECT
public:
    explicit ProtocolsList(QObject *parent = 0);

signals:

public slots:

};

}}}

#endif // PROTOCOLSLIST_H
