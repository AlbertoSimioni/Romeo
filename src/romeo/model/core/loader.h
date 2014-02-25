/**
* \file modelcore.h
* \author Matteo Pozza
* \date 2014-02-17
**
* \brief  Header della classe Loader del package romeo::model::core
*/

#include <QDir>
#include <QDomNode>
#include <src/romeo/model/protocols/algorithms/algorithmslist.h>
#include <src/romeo/model/protocols/features/featureslist.h>
#include <src/romeo/model/protocols/protocolslist.h>
#ifndef LOADER_H
#define LOADER_H


namespace romeo {
namespace model {
namespace core{

/**
 * \brief La classe Loader da completare
 *
 * Descrizione dettagliata
 */
class Loader: public QObject
{
    Q_OBJECT
public:
    /*!
     * \brief Metodo statico che ritorna l'istanza del Loader, in caso sia la prima volta ad essere invocato
     *  si preoccupa anche di costruire l'istanza.
     */
    static Loader* getInstance(QObject* parent);
    bool loadAlgorithms(QString algFile, protocols::algorithms::AbstractAlgorithm* algorithmList);
    bool loadFeatures(const QString &featFile, protocols::features::FeaturesList* featureList);
private:
    /*!
     * \brief Costruttore privato, poiché la classe Loader implementa il design pattern singleton
     */
    Loader(QObject *parent=0);
    /*!
     * \brief Campo dati statico che contiene il riferimento all'unica istanza del Loader
     */
    static Loader* instance;
    static bool parseFeature(protocols::features::FeaturesList* featureList, const QDomNode &node);
    static bool parseAlgorithm(protocols::algorithms::AlgorithmsList* algorithmsList, const QDomNode &node);
    static bool parseProtocol(protocols::ProtocolsList* protocolsList, const QDomNode &node);
};
}}}

#endif // LOADER_H
