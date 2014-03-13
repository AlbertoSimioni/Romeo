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
 * \brief Classe che rappresenta l'algoritmo di clustering Hierarchical. Questa classe è stata progettata seguendo il design pattern Object Adapter: la classe estende AbstractAlgorithm e adatta la firma dell'algoritmo Hierarchical contenuta nella classe CCluster. Inoltre la classe realizza il design pattern Singleton, poiché l'entità rappresentata non deve avere più di un'istanza.
 *
 * Mette a disposizione i metodi per eseguire l'algoritmo Hierarchical sui dati da analizzare.
 */


class Hierarchical : public AbstractAlgorithm
{
public:
    /*!
     * \brief Metodo statico che ritorna l'istanza dello Hierarchical, in caso sia la prima volta ad essere invocato
     *  si preoccupa anche di costruire l'istanza.
     */
    static Hierarchical* getInstance(QList< AbstractAlgorithm::AlgorithmParameter > par, QString name, QString desc);

    static int** replicate(int* single,int nrows,int ncols);
    /*!
     * \brief Implementazione del metodo virtuale pure presente in AbstractAlgorithm, eseguendo
     * l'algoritmo Hierarchical, utilizza l'algoritmo presente nella libreria C Cluster.
     * \param data RawData su cui effettuare l'algoritmo di clustering ha dimensioni nrows x ncols.
     * \param mask Maschera binaria con dimensione nrows.
     * \param nrows Numero di righe degli array data e mask.
     * \param ncols Numero di colonne dell'array data.
     * \param clusterid Array di dimensione nrows in cui verranno inseriti i risultati delle analisi tramite side-effect.
     * In particolare per ogni elemento dell'array viene inserito il cluster di appartenenza
     * \param nClusters Numero di cluster con cui eseguire l'algoritmo.
     * \param parameters Vettore contenente i parametri definibili dall'utente, che variano per ogni algoritmo.
     * \return Ritorna true se le analisi sono state eseguite correttamente altrimenti ritorna false
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
