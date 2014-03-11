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
    /*!
     * \brief Costruisce una nuova feature del primo ordine con i parametri indicati.
     * \param featureName Nome della feature da costruire.
     * \param dylp Percorso al file contenente la libreria dinamica della feature.
     * \param dyfn Nome della funzione da utilizzare per eseguire la feature.
     * \param description Descrizione della feature.
     */
    FirstOrderFeature(QString n,QString dylp,QString dyfn,QString desc = QString());

    /*!
     * \brief Override del metodo astratto di AbstractFeature
     */
    FeatureType getType();
};
}}}}
#endif // FIRSTORDERFEATURE_H
