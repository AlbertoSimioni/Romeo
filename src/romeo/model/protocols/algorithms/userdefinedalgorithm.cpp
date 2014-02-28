#include "userdefinedalgorithm.h"
using namespace romeo::model::protocols::algorithms;
/*UserDefinedAlgorithm::UserDefinedAlgorithm()
{
}
*/



QString UserDefinedAlgorithm::getDynamicLibraryPath() const
{
    return dynamicLibraryPath;
}

QString UserDefinedAlgorithm::getDynamicFunctionName() const
{
    return dynamicFunctionName;
}

UserDefinedAlgorithm::UserDefinedAlgorithm(QList< AbstractAlgorithm::AlgorithmParameter > par, QString name, QString desc, QString dylp, QString dyfn): AbstractAlgorithm(name,par,desc), dynamicLibraryPath(dylp), dynamicFunctionName(dyfn)
{

}

bool UserDefinedAlgorithm::execute(double **data, int *mask, int nrows, int ncols, int *clusterid, QList<QString> parameters)
{
 return true;
}
