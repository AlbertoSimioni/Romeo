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
 * \brief Classe astratta che rappresenta un feature extractor utilizzato per ricavare da immagini statiche delle particolari caratteristiche.
 *
 * Oltre alle funzionalità ereditate da AbstractFeature, contiene le informazioni comuni e necessarie a tutti i tipi di feature extractor che lavorano su immagini statiche e mette a disposizione i metodi per la modifica e il reperimento di tali informazioni.
 */


class AbstractStaticFeature : public AbstractFeature
{
public:
    /*!
     * \brief Costruisce una nuova feature con i parametri indicati.
     * \param featureName Nome della feature da costruire.
     * \param dylp Percorso al file contenente la libreria dinamica della feature.
     * \param dyfn Nome della funzione da utilizzare per eseguire la feature.
     * \param description Descrizione della feature.
     */
    AbstractStaticFeature(QString n,QString dylp,QString dyfn,QString desc = QString());

    //virtual void execute() = 0;//non è un override perché i parametri tra le feature statiche e dinamiche sono diversi
};
}}}}
#endif // ABSTRACTSTATICFEATURE_H
