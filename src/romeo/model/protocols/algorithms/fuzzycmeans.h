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
 * \brief Classe che rappresenta l'algoritmo di clustering Fuzzy C Means. Questa classe è stata progettata seguendo il design pattern Object Adapter: FuzzyCMeans implementa la classe astratta AbstractAlgorithm e adatta la firma dell'algoritmo Fuzzy C Means contenuta nella classe CCluster. Inoltre la classe realizza il design pattern Singleton, poiché l'entità rappresentata non deve avere più di un'istanza.
 *
 * Mette a disposizione i metodi per eseguire l'algoritmo Fuzzy C Means sui dati da analizzare.
 */


class FuzzyCMeans : public AbstractAlgorithm
{
public:
    /*!
     * \brief Metodo statico che ritorna l'istanza del FuzzyCMeans, in caso sia la prima volta ad essere invocato
     *  si preoccupa anche di costruire l'istanza.
     * \param par Lista dei parametri dell'algoritmo.
     * \param name Nome dell'algoritmo di clustering.
     * \param desc Descrizione dell'algoritmo.
     */
    static FuzzyCMeans* getInstance(QList< AbstractAlgorithm::AlgorithmParameter > par, QString name, QString desc);
    /*!
     * \brief Metodo che esegue l'algoritmo di clustering. Ritorna true se l'esecuzione ha avuto successo.
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
    FuzzyCMeans(QList< AbstractAlgorithm::AlgorithmParameter > par, QString name, QString desc);
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
