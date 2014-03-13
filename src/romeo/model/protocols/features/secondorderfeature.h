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
 * \brief Classe che rappresenta un feature extractor del secondo ordine applicabile su immagini statiche. Ogni istanza della classe rappresenta un diverso feature extractor e dovrà tenere traccia della libreria dinamica contenente la funzione che implementa il feature extractor.
 *
 * Questa classe eredita dalla classe AbstractStaticFeature e mette a disposizione i metodi per estrarre una feature del secondo ordine da un'immagine statica. In particolare la classe è in grado di calcolare la \underline{GLCM}.
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
