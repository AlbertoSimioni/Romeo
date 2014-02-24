#include "abstractalgorithm.h"
using namespace romeo::model::protocols::algorithms;
/*AbstractAlgorithm::AbstractAlgorithm(QList<AlgorithmParameter> p, QString n, QString d)
{
}
*/


AbstractAlgorithm::AlgorithmParameter::AlgorithmParameter(QString parameterName, ParameterType parType, QString defaultPar){
    name = parameterName;
    type = parType;
    defaultParameter = defaultPar;
}

QString AbstractAlgorithm::AlgorithmParameter::getName() const
{
    return name;
}


AbstractAlgorithm::ParameterType AbstractAlgorithm::AlgorithmParameter::getType() const
{
    return type;
}


QString AbstractAlgorithm::AlgorithmParameter::getDefaultParameter() const
{
    return defaultParameter;
}







AbstractAlgorithm::AbstractAlgorithm()
{

}

AbstractAlgorithm::AbstractAlgorithm(QString n,QList<AlgorithmParameter>par, QString d): name(n), parameters(par), description(d)
{

}

QString AbstractAlgorithm::getDescription() const
{
    return description;
}

QList<AbstractAlgorithm::AlgorithmParameter > AbstractAlgorithm::getParameters() const
{
    return parameters;
}


QString AbstractAlgorithm::getName() const
{
    return name;
}


