/**
* \file modelcore.h
* \author Alberto Cavallarin
* \date 17-02-2014
**
* \brief  Header della classe FirstOrderFeature del package romeo::model::protocols::features
*/

#ifndef FIRSTORDERFEATURE_H
#define FIRSTORDERFEATURE_H
#include"abstractstaticfeature.h"

namespace romeo {
namespace model {
namespace protocols{
namespace features{


/**
 * \brief La classe FirstOrderFeature da completare
 *
 * Descrizione dettagliata
 */
class FirstOrderFeature : public AbstractStaticFeature
{
public:
    FirstOrderFeature(QString n,QString dylp,QString dyfn,QString desc = QString());

    /*!
     * \brief Override del metodo astratto di AbstractFeature
     */
    FeatureType getType();
};
}}}}
#endif // FIRSTORDERFEATURE_H
