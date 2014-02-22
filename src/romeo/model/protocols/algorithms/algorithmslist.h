/**
* \file algorithmslist.h
* \author Alberto Cavallarin
* \date 17-02-2014
**
* \brief  Header della classe AlgorithmsList del package romeo::model::protocols::features
*/

#ifndef ALGORITHMSLIST_H
#define ALGORITHMSLIST_H

#include"abstractalgorithm.h"
#include <QObject>
#include <QList>
namespace romeo {
namespace model {
namespace protocols{
namespace algorithms{

/**
 * \brief La classe AlgorithmsList da completare
 *
 * Descrizione dettagliata
 */

class AlgorithmsList: public QObject
{
    Q_OBJECT
public:

    explicit AlgorithmsList(QObject *parent = 0);
    static AlgorithmsList* getInstance(QObject *parent=0);
    /*!
     * \brief Inserisce nella lista degli algoritmi un nuovo algoritmo di clustering con i parametri passati.
     * \param name Nome dell'algoritmo di clustering da inserire
     * \param description Descrizione dell'algoritmo di clustering da inserire
     * \param parameters Parametri dell'algoritmo di clustering da inserire
     */
    void addAlgorithm(QString name, QString description, QList<AbstractAlgorithm::AlgorithmParameter> parameters);
    /*!
     * \brief Aggiunge alla lista degli algoritmi, l'algoritmo passato per riferimento
     */
    void addAlgorithm(AbstractAlgorithm* aa);
signals:
    /*!
     * \brief Segnale che indica una modifica alla lista degli algoritmi
     */
    void algorithmsListModified();
private:
    /*!
     * \brief Il vettore contiene la lista degli algoritmi presenti nel programma
     */
    QList<AbstractAlgorithm*> algorithms;
    static AlgorithmsList* instance;
};
}}}}
#endif // ALGORITHMSLIST_H
