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


bool KMeans::execute(double **data, int *mask, int nrows, int ncols, int *clusterid,int nclusters, QList<QString> parameters){

    int** mask2;
    // errore
    double error;
    // flag se ci sono stati errori
    int ifound = 1;
    char distance = parameters.at(0).at(0).toLatin1();
    if((distance != 'e') && (distance != 'b') && (distance != 'c')){
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
    return ifound;
}
