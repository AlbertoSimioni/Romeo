#include "hierarchical.h"
using namespace romeo::model::protocols::algorithms;

Hierarchical* Hierarchical::instance=0;
Hierarchical *Hierarchical::getInstance()
{
    if(instance==0)
    {
        //instance=new Hierarchical();
    }
    return instance;
}

Hierarchical::Hierarchical()
{
}
