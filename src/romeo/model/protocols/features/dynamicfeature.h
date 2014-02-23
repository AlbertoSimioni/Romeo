/**
* \file modelcore.h
* \author Alberto Cavallarin
* \date 17-02-2014
**
* \brief  Header della classe DynamicFeature del package romeo::model::protocols::features
*/

#ifndef DYNAMICFEATURE_H
#define DYNAMICFEATURE_H

#include"abstractfeature.h"

namespace romeo {
namespace model {
namespace protocols{
namespace features{

/**
 * \brief La classe DynamicFeature da completare
 *
 * Descrizione dettagliata
 */
class DynamicFeature : public AbstractFeature
{
public:
    DynamicFeature(QString n,QString dylp,QString dyfn,QString desc = QString());
    void execute();

    /*!
     * \brief Override del metodo astratto di AbstractFeature
     */
    FeatureType getType();
};
}}}}
#endif // DYNAMICFEATURE_H
