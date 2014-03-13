/**
* \file fuzzycmeans.cpp
* \author Alberto Cavallarin
* \date 17-02-2014
**
* \brief  Header della classe FuzzyCMeans del package romeo::model::protocols::features
*/

#include "fuzzycmeans.h"
#include "ext/cluster.h"
using namespace romeo::model::protocols::algorithms;

FuzzyCMeans* FuzzyCMeans::instance=0;
FuzzyCMeans *FuzzyCMeans::getInstance(QList< AbstractAlgorithm::AlgorithmParameter > par, QString name, QString desc)
{
    if(instance == 0)
    {
        instance=new FuzzyCMeans(par,name,desc);
    }
    return instance;
}

FuzzyCMeans::FuzzyCMeans(QList< AbstractAlgorithm::AlgorithmParameter > par, QString name, QString desc):
    AbstractAlgorithm(name,par,desc)
{

}


bool FuzzyCMeans::execute(double **data, int *mask, int nrows, int ncols, int *clusterid,int nclusters, QList<QString> parameters){
    bool ok = true;
    double epsilon = parameters.at(0).toDouble(&ok);

    bool ok2;
    int fuzzyness =  parameters.at(1).toInt(&ok2);
    // vettore dei pesi: tutti a 1
    if(ok && ok2){
        fcm(nclusters, nrows, ncols, data, epsilon, fuzzyness, clusterid,mask);
    return true;
    }
    else return false;
}
