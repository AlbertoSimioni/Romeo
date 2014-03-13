/**
* \file secondorderfeature.h
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
    /*!
     * \brief Costruisce una nuova feature del secondo ordine con i parametri indicati.
     * \param featureName Nome della feature da costruire.
     * \param dylp Percorso al file contenente la libreria dinamica della feature.
     * \param dyfn Nome della funzione da utilizzare per eseguire la feature.
     * \param description Descrizione della feature.
     */
    SecondOrderFeature(QString n,QString dylp,QString dyfn,QString desc = QString());

    /*!
     * \brief Override del metodo astratto di AbstractFeature che ritorna il tipo dinamico della feature invocata.
     */
    FeatureType getType();
};
}}}}
#endif // SECONDORDERFEATURE_H
