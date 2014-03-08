#include "hierarchical.h"

#ifndef CLUSTER
#include "ext/cluster.h"
#endif

using namespace romeo::model::protocols::algorithms;

Hierarchical* Hierarchical::instance=0;
Hierarchical *Hierarchical::getInstance(QList< AbstractAlgorithm::AlgorithmParameter > par, QString name, QString desc)
{
    if(instance == 0)
    {
        instance=new Hierarchical(par,name,desc);
    }
    return instance;
}

Hierarchical::Hierarchical(QList< AbstractAlgorithm::AlgorithmParameter > par, QString name, QString desc):
    AbstractAlgorithm(name,par,desc)
{

}

bool Hierarchical::execute(double **data, int *mask, int nrows, int ncols, int *clusterid,int nclusters, QList<QString> parameters){

    int** mask2;

    char distance = parameters.at(0).at(0).toLatin1();
    if((distance != 'e') && (distance != 'b') && (distance != 'c')){
        distance = 'e';
    }

    char linkage = parameters.at(1).at(0).toLatin1();
    if((linkage != 'a') && (linkage != 's') && (linkage != 'c')&& (linkage != 'm')){
        linkage = 's';
    }
    // vettore dei pesi: tutti a 1
    double* weight = new double[nrows];
    for(int j=0;j<nrows;j++) {
        weight[j] = 1.0;
    }
    hierarchicalAlgorithm(nclusters, nrows, ncols, data, mask2, weight, distance, 0, linkage, clusterid);
    return true;
}
