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
    /*!
     * \brief Costruisce una nuova feature con i parametri indicati.
     * \param featureName Nome della feature da costruire.
     * \param dylp Percorso al file contenente la libreria dinamica della feature.
     * \param dyfn Nome della funzione da utilizzare per eseguire la feature.
     * \param description Descrizione della feature.
     */
    DynamicFeature(QString n,QString dylp,QString dyfn,QString desc = QString());
    void execute();

    /*!
     * \brief Override del metodo astratto di AbstractFeature che ritorna il tipo dinamico della feature.
     */
    FeatureType getType();
};
}}}}
#endif // DYNAMICFEATURE_H
