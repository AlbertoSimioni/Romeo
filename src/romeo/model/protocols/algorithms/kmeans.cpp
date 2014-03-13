/**
* \file kmeans.cpp
* \author Alberto Cavallarin
* \date 17-02-2014
**
* \brief  Header della classe KMeans del package romeo::model::protocols::features
*/


#include "kmeans.h"
#ifndef CLUSTER
#include "ext/cluster.h"
#endif
using namespace romeo::model::protocols::algorithms;

KMeans* KMeans::instance=0;
KMeans *KMeans::getInstance(QList< AbstractAlgorithm::AlgorithmParameter > par, QString name, QString desc)
{
    if(instance == 0)
    {
        instance=new KMeans(par,name,desc);
    }
    return instance;
}

KMeans::KMeans(QList< AbstractAlgorithm::AlgorithmParameter > par, QString name, QString desc):
    AbstractAlgorithm(name,par,desc)
{

}

int** KMeans::replicate(int* single,int nrows,int ncols) {
    int** result = new int*[nrows];
    for(int i=0;i<nrows;i++)
        result[i] = new int[ncols];
    // replicazione
    for(int i=0;i<nrows;i++) {
        for(int j=0;j<ncols;j++)
            result[i][j]=single[i];
    }
    // non cancello la mask singola, se ne occupa il metodo templateExecute
    return result;
}


bool KMeans::execute(double **data, int *mask, int nrows, int ncols, int *clusterid,int nclusters, QList<QString> parameters){

    int** mask2 = replicate(mask,nrows,ncols);
    // errore
    double error;
    // flag se ci sono stati errori
    int ifound = 1;
    char distance = parameters.at(0).at(0).toLatin1();
    if((distance != 'e') && (distance != 'b') && (distance != 'c') && (distance != 'a') && (distance != 'u') && (distance != 'x') && (distance != 's') && (distance != 'k')){
        distance = 'e';
    }
    bool ok;
    int maxIt =  parameters.at(1).toInt(&ok);
    // vettore dei pesi: tutti a 1
    double* weight = new double[nrows];
    for(int j=0;j<nrows;j++) {
        weight[j] = 1.0;
    }
    kcluster(nclusters, nrows, ncols, data, mask2, weight, 0, maxIt, 'a', distance, clusterid, &error, &ifound);
    // delete della maschera
    for(int i=0;i<nrows;i++)
        delete[] mask2[i];
    delete[] mask2;
    // delete dei pesi
    delete[] weight;
    return ifound;
}
