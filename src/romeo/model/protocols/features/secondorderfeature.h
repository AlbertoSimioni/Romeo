/**
* \file modelcore.h
* \author Alberto Cavallarin
* \date 17-02-2014
**
* \brief  Header della classe SecondOrderFeature del package romeo::model::protocols::features
*/

#ifndef SECONDORDERFEATURE_H
#define SECONDORDERFEATURE_H
#include"abstractstaticfeature.h"

namespace romeo {
namespace model {
namespace protocols{
namespace features{


/**
 * \brief La classe SecondOrderFeature da completare
 *
 * Descrizione dettagliata
 */
class SecondOrderFeature : public AbstractStaticFeature
{
public:
    SecondOrderFeature(QString n,QString dylp,QString dyfn,QString desc = QString());

    /*!
     * \brief Override del metodo astratto di AbstractFeature
     */
    FeatureType getType();
};
}}}}
#endif // SECONDORDERFEATURE_H
