/**
* \file handleriostatic.cpp
* \author Matteo Pozza
* \date 2014-02-17
**
* \brief Header della classe HandlerIOStatic del package romeo::model::imageIO
*/

#include "handleriostatic.h"

using namespace romeo::model::imageIO;

HandlerIOStatic* HandlerIOStatic::instance=0;
HandlerIOStatic *HandlerIOStatic::getInstance()
{
    if(instance == 0)
    {
        instance= new HandlerIOStatic();
    }
    return instance;
}


HandlerIOStatic::HandlerIOStatic()
{
}
