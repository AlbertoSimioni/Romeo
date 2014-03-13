/**
* \file dynamicfeature.h
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
 * \brief Classe che rappresenta un feature extractor applicabile su immagini dinamiche. Ogni istanza della classe rappresenta un diverso feature extractor e dovrà tenere traccia della libreria dinamica contenente la funzione che implementa il feature extractor.
 *
 * Questa classe eredita dalla classe AbstractFeature e mette a disposizione i metodi per estrarre una feature da un'immagine dinamica.
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
