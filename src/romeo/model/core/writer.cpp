#include "writer.h"
using namespace romeo::model::core;

Writer* Writer::instance=0;

Writer *Writer::getInstance()
{
    if(instance == 0)
    {
        instance=new Writer();
    }
    return instance;
}

Writer::Writer()
{
}
