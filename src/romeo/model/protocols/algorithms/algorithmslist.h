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
#include <QVector>
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
private:
    /*!
     * \brief Il vettore contiene la lista degli algoritmi presenti nel programma
     */
    QVector<AbstractAlgorithm*> algorithms;
public:

    explicit AlgorithmsList(QObject *parent = 0);
    /*!
     * \brief Inserisce nella lista degli algoritmi un nuovo algoritmo di clustering con i parametri passati.
     * \param name Nome dell'algoritmo di clustering da inserire
     * \param description Descrizione dell'algoritmo di clustering da inserire
     * \param parameters Parametri dell'algoritmo di clustering da inserire
     */
    void addAlgorithm(QString name, QString description, QVector<AbstractAlgorithm::AlgorithmParameter> parameters);
    /*!
     * \brief Aggiunge alla lista degli algoritmi, l'algoritmo passato per riferimento
     */
    void addAlgorithm(AbstractAlgorithm* aa);
};
}}}}
#endif // ALGORITHMSLIST_H
