/**
* \file dynamicprotocol.h
* \author Matteo Pozza
* \date 2014-02-17
**
* \brief Header della classe DynamicProtocol del package romeo::model::protocols
*/

#ifndef DYNAMICPROTOCOL_H
#define DYNAMICPROTOCOL_H
#include "abstractprotocol.h"

namespace romeo {
namespace model {
namespace protocols{

/**
 * \brief La classe DynamicProtocol rappresenta i protocolli che agiscono su immagini di tipo dinamico,
 **
 *  e quindi accettano soggetti di tipo Subject2D col tempo e Subject3D col tempo.
 */
class DynamicProtocol : public AbstractProtocol
{
public:

    DynamicProtocol(QString nomeP, QString desc, algorithms::AbstractAlgorithm* alg, QList<features::AbstractFeature*> feat,bool testProtocol);

    /*!
     * \brief Override del metodo execute della classe astratta AbstractProtocol
     * \param subject Il soggetto su cui eseguire il protocollo
     */
    virtual void execute(datasets::AbstractSubject *subject);
    /*!
     * \brief Funzione virtuale che ritorna il tipo del protocollo corrente, per la classe DynamicProtocol ritornerà ProtocolType::DYNAMIC. La funzione è override di quella definita nella superclasse e può essere chiamata avendo solo un riferimento a AbstractProtocol.
     */
    virtual ProtocolType getType();
    virtual int getWindowSize() const;
    virtual int getDistanceToGlcm() const;
};
}}}
#endif // DYNAMICPROTOCOL_H
