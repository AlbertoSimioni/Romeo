/**
* \file modelcore.h
* \author Alberto Cavallarin
* \date 17-02-2014
**
* \brief  Header della classe AbstractStaticFeature del package romeo::model::protocols::features
*/

#ifndef ABSTRACTSTATICFEATURE_H
#define ABSTRACTSTATICFEATURE_H
#include"abstractfeature.h"

namespace romeo {
namespace model {
namespace protocols{
namespace features{


/**
 * \brief La classe AbstractStaticFeature da completare
 *
 * Descrizione dettagliata
 */


class AbstractStaticFeature : public AbstractFeature
{
public:
    AbstractStaticFeature(QString n,QString dylp,QString dyfn,QString desc = QString());

    //virtual void execute() = 0;//non è un override perché i parametri tra le feature statiche e dinamiche sono diversi
};
}}}}
#endif // ABSTRACTSTATICFEATURE_H
