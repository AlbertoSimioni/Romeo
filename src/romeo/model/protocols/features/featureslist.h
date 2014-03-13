/**
* \file featureslist.h
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
 * \brief FeaturesList rappresenta la lista delle feature caricate nell'applicazione e che possono essere usate per operazioni di estrazione feature.
 *
 * FeatureList espone i metodi per aggiungere feature alla lista, rimuoverle oppure per cercare se un feature è presente o meno.
 */


class FeaturesList : public QObject
{
    Q_OBJECT

public:
    /*!
     * \brief Metodo statico che ritorna l'istanza di FeaturesList, in caso sia la prima volta ad essere invocato
     *  si preoccupa anche di costruire l'istanza.
     */
    static FeaturesList* getInstance(QObject *parent=0);
    /*!
      * \brief Distruttore della lista delle feature che si preoccupa di eliminare in modo opportuno i riferimenti alle feature senza lasciare dati inutilizzati in memoria.
      */
    ~FeaturesList();
    /*!
     * \brief Inserisce nella lista dei protocolli un nuovo protocollo definito dai parametri passati
     * \param name Nome della feature da inserire
     * \param type Il tipo della feature tra i tipi disponibili: FIRSTORDER, SECONDORDER e DYNAMIC
     * \param description Descrizione dell'algoritmo di clustering da inserire
     * \param dylp Il percorso alla libreria dinamica dove si trova la feature
     * \param dyfn Il nome della funzione contenuto nella libreria dinamica
     */
    void addFeature(const QString& name, FeatureType type, const QString& description, const QString& dylp, const QString& dyfn);
    /*!
     * \brief Aggiunge alla lista la feature passata per riferimento.
     */
    void addFeature(AbstractFeature* aa);

    /*!
     * \brief Ritorna l'intera lista di features del modello.
     */
    QList<AbstractFeature*> getFeaturesList();
    /*!
     * \brief Ritorna un puntatore alla feature con il nome passato come parametro.
     */
    AbstractFeature* getFeature(QString feature) const;

signals:
    /*!
     * \brief Segnale che indica una modifica alla lista delle feature, come un nuovo inserimento, una eliminazione o una modifica a una feature.
     */
    void featuresListModified();
private:
    /*!
     * \brief Costruttore privato, poiché la classe FeaturesList implementa il design pattern singleton
     */
    explicit FeaturesList(QObject *parent = 0);
    /*!
     * \brief La lista delle feature presenti nel programma
     */
    QList<AbstractFeature*> features;

    /*!
     * \brief Campo dati statico che contiene il riferimento all'unica istanza della lista delle feature
     */
    static FeaturesList* instance;

};
}}}}
#endif // FEATURESLIST_H
