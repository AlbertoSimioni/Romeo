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
    Hierarchical();

    /*!
     * \brief Implementazione del metodo virtuale pure presente in AbstractAlgorithm, eseguendo
     * l'algoritmo Hierarchical, utilizza l'algoritmo presente nella libreria C Cluster.
     */
    //virtual bool execute(double **data, int *mask, int nrows, int ncols, int *clusterid, QVector<QString> parameters);
};
}}}}
#endif // HIERARCHICAL_H
