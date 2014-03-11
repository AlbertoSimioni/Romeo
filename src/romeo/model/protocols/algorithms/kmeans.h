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
     * \brief Metodo che fa una copia dei dati in input e li replica su un numero specifico di colonne fino ad ottenere una matrice a partire da un vettore.
     * \param single Array di partenza
     * \param nrows Numero di righe
     * \param ncols Numero di colonne
     * \return
     */
    static int** replicate(int* single,int nrows,int ncols);
    /*!
     * \brief Implementazione del metodo virtuale pure presente in AbstractAlgorithm, eseguendo
     * l'algoritmo K-Means, utilizza l'algoritmo presente nella libreria C Cluster.
     * \param data RawData su cui effettuare l'algoritmo di clustering ha dimensioni nrows x ncols.
     * \param mask Maschera binaria con dimensione nrows.
     * \param nrows Numero di righe degli array data e mask.
     * \param ncols Numero di colonne dell'array data.
     * \param clusterid Array di dimensione nrows in cui verranno inseriti i risultati delle analisi tramite side-effect.
     * In particolare per ogni elemento dell'array viene inserito il cluster di appartenenza
     * \param parameters Vettore contenente i parametri definibili dall'utente, che variano per ogni algoritmo.
     * \return Ritorna true se le analisi sono state eseguite correttamente altrimenti ritorna false
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
