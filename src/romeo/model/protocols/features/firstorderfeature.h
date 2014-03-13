/**
* \file firstorderfeature.h
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
 * \brief Classe che rappresenta un feature extractor del primo ordine applicabile su immagini statiche. Ogni istanza della classe rappresenta un diverso feature extractor e dovrà tenere traccia della libreria dinamica contenente la funzione che implementa il feature extractor.
 *
 * Questa classe eredita dalla classe AbstractStaticFeature e mette a disposizione i metodi per estrarre una feature del primo ordine da un'immagine statica.
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
