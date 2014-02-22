#include "userdefinedalgorithm.h"
using namespace romeo::model::protocols::algorithms;
/*UserDefinedAlgorithm::UserDefinedAlgorithm()
{
}
*/


UserDefinedAlgorithm::UserDefinedAlgorithm(QList< AbstractAlgorithm::AlgorithmParameter > par, QString name, QString desc, QString dylp, QString dyfn): AbstractAlgorithm(name, desc), dynamicLibraryPath(dylp), dynamicFunctionName(dyfn)
{

}

bool UserDefinedAlgorithm::execute(double **data, int *mask, int nrows, int ncols, int *clusterid, QList<QString> parameters)
{
 return true;
}
