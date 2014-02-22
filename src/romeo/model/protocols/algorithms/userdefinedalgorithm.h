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
    UserDefinedAlgorithm(QList<AlgorithmParameter> par, QString name, QString desc, QString dylp, QString dyfn);

    bool execute(double **data, int *mask, int nrows, int ncols, int *clusterid, QList<QString> parameters);
};
}}}}
#endif // USERDEFINEDALGORITHM_H
