#include "kmeans.h"
using namespace romeo::model::protocols::algorithms;

KMeans* KMeans::instance=0;
KMeans *KMeans::getInstance()
{
    if(instance == 0)
    {
        //instance= new KMeans();
    }
    return instance;
}

KMeans::KMeans()
{
}
