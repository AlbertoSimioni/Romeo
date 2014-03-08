#include "userdefinedalgorithm.h"

using namespace romeo::model::protocols::algorithms;



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

bool UserDefinedAlgorithm::execute(double **data, int *mask, int nrows, int ncols, int *clusterid,int nclusters, QList<QString> parameters)
{
    typedef void (*MyPrototype)(double** data, int* mask, int nrows, int ncols,int* clusterid,int nclusters, std::vector<std::string> parameters);
    MyPrototype algorithm = (MyPrototype) QLibrary::resolve(dynamicLibraryPath,dynamicFunctionName.toStdString().c_str());
    // converti QList<QString> in vector<std::string>
    std::vector<std::string> stringParameters;
    QList<QString>::iterator iterator;
    for (iterator = parameters.begin(); iterator != parameters.end(); ++iterator)
        stringParameters.push_back((*iterator).toStdString());
    // esegui l'algoritmo
    algorithm(data,mask,nrows,ncols,clusterid,nclusters,stringParameters);
    // non c'è nulla da deallocare
    return true;
}
