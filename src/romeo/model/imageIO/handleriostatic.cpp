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
