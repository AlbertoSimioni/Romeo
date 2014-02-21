#include "fuzzycmeans.h"
using namespace romeo::model::protocols::algorithms;

FuzzyCMeans* FuzzyCMeans::instance=0;
FuzzyCMeans *FuzzyCMeans::getInstance()
{
    if(instance == 0)
    {
        //instance=new FuzzyCMeans();
    }
    return instance;
}

FuzzyCMeans::FuzzyCMeans()
{
}
