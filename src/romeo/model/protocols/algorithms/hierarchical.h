/**
* \file hierarchical.h
* \author Alberto Cavallarin
* \date 17-02-2014
**
* \brief  Header della classe Hierarchical del package romeo::model::protocols::features
*/


#ifndef HIERARCHICAL_H
#define HIERARCHICAL_H

#include"abstractalgorithm.h"

namespace romeo {
namespace model {
namespace protocols{
namespace algorithms{

/**
 * \brief La classe Hierarchical da completare
 *
 * Descrizione dettagliata
 */


class Hierarchical : public AbstractAlgorithm
{
public:
    /*!
     * \brief Metodo statico che ritorna l'istanza dello Hierarchical, in caso sia la prima volta ad essere invocato
     *  si preoccupa anche di costruire l'istanza.
     */
    static Hierarchical* getInstance(QList< AbstractAlgorithm::AlgorithmParameter > par, QString name, QString desc);
    /*!
     * \brief replicate
     * \param single
     * \param nrows
     * \param ncols
     * \return
     */
    static int** replicate(int* single,int nrows,int ncols);
    /*!
     * \brief Implementazione del metodo virtuale pure presente in AbstractAlgorithm, eseguendo
     * l'algoritmo Hierarchical, utilizza l'algoritmo presente nella libreria C Cluster.
     */
    virtual bool execute(double **data, int *mask, int nrows, int ncols, int *clusterid,int nclusters, QList<QString> parameters);
private:
    Hierarchical(QList< AbstractAlgorithm::AlgorithmParameter > par, QString name, QString desc);
    /*!
     * \brief Campo dati statico che contiene il riferimento all'unica istanza di Hierarchical
     */
    static Hierarchical* instance;
};
}}}}
#endif // HIERARCHICAL_H
