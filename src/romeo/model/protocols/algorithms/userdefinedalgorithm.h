/**
* \file userdefinedalgorithm.h
* \author Alberto Cavallarin
* \date 17-02-2014
**
* \brief  Header della classe UserDefinedAlgorithm del package romeo::model::protocols::features
*/


#ifndef USERDEFINEDALGORITHM_H
#define USERDEFINEDALGORITHM_H

#include"abstractalgorithm.h"
#include<QString>
#include<QLibrary>
#include<vector>
namespace romeo {
namespace model {
namespace protocols{
namespace algorithms{

/**
 * \brief La classe UserDefinedAlgorithm da completare
 *
 * Descrizione dettagliata
 */




class UserDefinedAlgorithm : public AbstractAlgorithm
{
    /*!
     * \brief Stringa contenente il percorso nel file system con la libreria dinamica contenete il codice dell'algoritmo di clustering definito dall'utente
     */
    QString dynamicLibraryPath;
    /*!
     * \brief Stringa contente il nome della funzione all'interno della libreria dinamica.
     */
    QString dynamicFunctionName;
public:
    /*!
     * \brief Costruisce un nuovo algoritmo definito dall'utente.
     * \param par Parametri dell'algoritmo.
     * \param name Nome dell'algoritmo.
     * \param desc Descrizione dell'algoritmo.
     * \param dylp Percorso nel file system con la libreria dinamica contenete il codice dell'algoritmo di clustering definito dall'utente.
     * \param dyfn Nome della funzione all'interno della libreria dinamica.
     */
    UserDefinedAlgorithm(QList<AlgorithmParameter> par, QString name, QString desc, QString dylp, QString dyfn);
    /*!
     * \brief Esegue sul subject passato l'algoritmo di clustering definito dall'utente.
     * \param data RawData su cui effettuare l'algoritmo di clustering ha dimensioni nrows x ncols.
     * \param mask Maschera binaria con dimensione nrows.
     * \param nrows Numero di righe degli array data e mask.
     * \param ncols Numero di colonne dell'array data.
     * \param clusterid Array di dimensione nrows in cui verranno inseriti i risultati delle analisi tramite side-effect.
     * In particolare per ogni elemento dell'array viene inserito il cluster di appartenenza
     * \param nclusters Numero di cluster da considerare durante l'esecuzione.
     * \param parameters Vettore contenente i parametri definibili dall'utente, che variano per ogni algoritmo.
     * \return Ritorna true se le analisi sono state eseguite correttamente altrimenti ritorna false
     */
    bool execute(double **data, int *mask, int nrows, int ncols, int *clusterid,int nclusters, QList<QString> parameters);
    /*!
     * \brief Ritorna la posizione nel file system dove si trova la libreria.
     */
    QString getDynamicLibraryPath() const;
    /*!
     * \brief Ritorna il nome della funzione contenuta nella libreria dinamica.
     */
    QString getDynamicFunctionName() const;
};
}}}}
#endif // USERDEFINEDALGORITHM_H
