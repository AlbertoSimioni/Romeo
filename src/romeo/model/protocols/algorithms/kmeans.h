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
    /*!
     * \brief Metodo statico che ritorna l'istanza del KMeans, in caso sia la prima volta ad essere invocato
     *  si preoccupa anche di costruire l'istanza.
     */
    static KMeans* getInstance(QList< AbstractAlgorithm::AlgorithmParameter > par, QString name, QString desc);
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
     * l'algoritmo K-Means, utilizza l'algoritmo presente nella libreria C Cluster.
     */
    virtual bool execute(double **data, int *mask, int nrows, int ncols, int *clusterid,int nclusters, QList<QString> parameters);
private:
    KMeans(QList< AbstractAlgorithm::AlgorithmParameter > par, QString name, QString desc);
    /*!
     * \brief Campo dati statico che contiene il riferimento all'unica istanza di KMeans
     */
    static KMeans* instance;
};
}}}}
#endif // KMEANS_H
