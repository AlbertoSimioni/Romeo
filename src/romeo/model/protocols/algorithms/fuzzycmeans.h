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
    /*!
     * \brief Metodo statico che ritorna l'istanza del FuzzyCMeans, in caso sia la prima volta ad essere invocato
     *  si preoccupa anche di costruire l'istanza.
     */
    static FuzzyCMeans* getInstance();
    //virtual bool execute(double **data, int *mask, int nrows, int ncols, int *clusterid, QList<QString> parameters);
private:
    FuzzyCMeans();
    /*!
     * \brief Implementazione del metodo virtuale pure presente in AbstractAlgorithm, eseguendo
     * l'algoritmo Fuzzy C-Means, utilizza l'algoritmo presente nella libreria C Cluster.
     */

    /*!
     * \brief Campo dati statico che contiene il riferimento all'unica istanza del FuzzyCMeans
     */
    static FuzzyCMeans* instance;

};
}}}}
#endif // FUZZYCMEANS_H
