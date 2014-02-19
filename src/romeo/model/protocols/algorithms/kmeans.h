/**
* \file kmeans.h
* \author Alberto Cavallarin
* \date 17-02-2014
**
* \brief  Header della classe KMeans del package romeo::model::protocols::features
*/


#ifndef KMEANS_H
#define KMEANS_H

#include"abstractalgorithm.h"

namespace romeo {
namespace model {
namespace protocols{
namespace algorithms{

/**
 * \brief La classe KMeans da completare
 *
 * Descrizione dettagliata
 */


class KMeans : public AbstractAlgorithm
{
public:
    KMeans();

    /*!
     * \brief Implementazione del metodo virtuale pure presente in AbstractAlgorithm, eseguendo
     * l'algoritmo K-Means, utilizza l'algoritmo presente nella libreria C Cluster.
     */
    //virtual bool execute(double **data, int *mask, int nrows, int ncols, int *clusterid, QVector<QString> parameters);
};
}}}}
#endif // KMEANS_H
