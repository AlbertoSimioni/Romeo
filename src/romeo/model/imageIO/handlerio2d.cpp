#include "handlerio2d.h"
using namespace romeo::model::imageIO;

HandlerIO2D* HandlerIO2D::instance=0;
HandlerIO2D *HandlerIO2D::getInstance()
{
    if(instance == 0)
    {
        instance= new HandlerIO2D();
    }
    return instance;
}

HandlerIO2D::HandlerIO2D()
{
}
