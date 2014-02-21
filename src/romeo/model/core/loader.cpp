#include "loader.h"
using namespace romeo::model::core;

Loader* Loader::instance=0;
Loader *Loader::getInstance()
{
    if(instance == 0){
        instance=new Loader();
    }
    return instance;
}

Loader::Loader()
{
}
