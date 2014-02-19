/**
* \file fuzzycmeans.h
* \author Alberto Cavallarin
* \date 17-02-2014
**
* \brief  Header della classe FuzzyCMeans del package romeo::model::protocols::features
*/


#ifndef FUZZYCMEANS_H
#define FUZZYCMEANS_H

#include"abstractalgorithm.h"

namespace romeo {
namespace model {
namespace protocols{
namespace algorithms{

/**
 * \brief La classe FuzzyCMeans da completare
 *
 * Descrizione dettagliata
 */


class FuzzyCMeans : public AbstractAlgorithm
{
public:


    FuzzyCMeans();

    /*!
     * \brief Implementazione del metodo virtuale pure presente in AbstractAlgorithm, eseguendo
     * l'algoritmo Fuzzy C-Means, utilizza l'algoritmo presente nella libreria C Cluster.
     */
    //virtual bool execute(double **data, int *mask, int nrows, int ncols, int *clusterid, QVector<QString> parameters);
};
}}}}
#endif // FUZZYCMEANS_H
