/**
* \file hierarchical.cpp
* \author Alberto Cavallarin
* \date 17-02-2014
**
* \brief  Header della classe Hierarchical del package romeo::model::protocols::features
*/


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

int** Hierarchical::replicate(int* single,int nrows,int ncols) {
    int** result = new int*[nrows];
    for(int i=0;i<nrows;i++)
        result[i] = new int[ncols];
    // replicazione
    for(int i=0;i<nrows;i++) {
        for(int j=0;j<ncols;j++)
            result[i][j]=single[i];
    }
    // non cancello la maschera singola, se ne occupa il metodo templateExecute
    return result;
}

bool Hierarchical::execute(double **data, int *mask, int nrows, int ncols, int *clusterid,int nclusters, QList<QString> parameters){

    int** mask2 = replicate(mask,nrows,ncols);

    char distance = parameters.at(0).at(0).toLatin1();
    if((distance != 'e') && (distance != 'b') && (distance != 'c') && (distance != 'a') && (distance != 'u') && (distance != 'x') && (distance != 's') && (distance != 'k')){
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
    // delete della maschera
    for(int i=0;i<nrows;i++)
        delete[] mask2[i];
    delete[] mask2;
    // delete dei pesi
    delete[] weight;
    return true;
}
