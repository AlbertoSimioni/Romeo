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
    QString dynamicLibraryPath;
    QString dynamicFunctionName;
public:
    UserDefinedAlgorithm();
    bool execute(double **data, double *mask, int nrows, int ncols, int *clusterid, QVector<QString> parameters);
};
}}}}
#endif // USERDEFINEDALGORITHM_H
