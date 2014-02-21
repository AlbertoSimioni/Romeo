/**
* \file modelcore.h
* \author Alberto Cavallarin
* \date 17-02-2014
**
* \brief  Header della classe DynamicFeature del package romeo::model::protocols::features
*/

#ifndef FEATURESLIST_H
#define FEATURESLIST_H

#include <QObject>
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


class FeaturesList : public QObject
{
    Q_OBJECT

public:
    explicit FeaturesList(QObject *parent = 0);

    /*!
     * \brief Inserisce nella lista dei protocolli un nuovo protocollo definito dai parametri passati
     * \param name Nome della feature da inserire
     * \param description Descrizione dell'algoritmo di clustering da inserire
     * \param parameters Parametri dell'algoritmo di clustering da inserire
     */
    void addFeature(QString name, QString description, QString dylp, QString dyfn);
    /*!
     * \brief Aggiunge alla lista degli algoritmi, l'algoritmo passato per riferimento
     */
    void addFeature(AbstractFeature* aa);

signals:
    /*!
     * \brief Segnale che indica una modifica alla lista delle feature
     */
    void featureListModified();
private:
    /*!
     * \brief Il vettore contiene la lista delle feature presenti nel programma
     */
    //QList<AbstractFeature*> features;

};
}}}}
#endif // FEATURESLIST_H
