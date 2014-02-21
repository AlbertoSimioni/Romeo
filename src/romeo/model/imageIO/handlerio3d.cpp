#include "handlerio3d.h"
using namespace romeo::model::imageIO;

HandlerIO3D* HandlerIO3D::instance=0;
HandlerIO3D *HandlerIO3D::getInstance()
{
    if(instance == 0)
    {
        instance= new HandlerIO3D();
    }
    return instance;
}

HandlerIO3D::HandlerIO3D()
{
}
