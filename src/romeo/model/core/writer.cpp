#include "writer.h"
using namespace romeo::model::core;

Writer* Writer::instance=0;

Writer *Writer::getInstance(QObject *parent)
{
    if(instance == 0)
    {
        instance=new Writer(parent);
    }
    return instance;
}

Writer::Writer(QObject* parent): QObject(parent)
{
}
