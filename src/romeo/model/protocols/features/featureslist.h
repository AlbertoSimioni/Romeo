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
    /*!
     * \brief Metodo statico che ritorna l'istanza di AlgorithmList, in caso sia la prima volta ad essere invocato
     *  si preoccupa anche di costruire l'istanza.
     */
    static FeaturesList* getInstance(QObject *parent=0);
    ~FeaturesList();
    /*!
     * \brief Inserisce nella lista dei protocolli un nuovo protocollo definito dai parametri passati
     * \param name Nome della feature da inserire
     * \param type Il tipo della feature tra i tipi disponibili: FIRSTORDER, SECONDORDER e DYNAMIC
     * \param description Descrizione dell'algoritmo di clustering da inserire
     * \param dylp Il percorso alla libreria dinamica dove si trova l'algoritmo della feature
     * \param dyfn Il nome della funzione contenuto nella libreria dinamica
     */
    void addFeature(const QString& name, FeatureType type, const QString& description, const QString& dylp, const QString& dyfn);
    /*!
     * \brief Aggiunge alla lista degli algoritmi, l'algoritmo passato per riferimento
     */
    void addFeature(AbstractFeature* aa);

    /*!
     * \brief Ritorna l'intera lista di features del modello.
     */
    QList<AbstractFeature*> getFeaturesList();
    AbstractFeature* getFeature(QString feature) const;

signals:
    /*!
     * \brief Segnale che indica una modifica alla lista delle feature
     */
    void featuresListModified();
private:
    /*!
     * \brief Costruttore privato, poiché la classe Loader implementa il design pattern singleton
     */
    explicit FeaturesList(QObject *parent = 0);
    /*!
     * \brief Il vettore contiene la lista delle feature presenti nel programma
     */
    QList<AbstractFeature*> features;


    /*!
     * \brief Campo dati statico che contiene il riferimento all'unica istanza della lista delle feature
     */
    static FeaturesList* instance;

};
}}}}
#endif // FEATURESLIST_H
