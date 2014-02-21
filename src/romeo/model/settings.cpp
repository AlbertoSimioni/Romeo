#include "settings.h"
using namespace romeo::model;

Settings* Settings::instance=0;

Settings *Settings::getInstance(QObject *parent)
{
    if(instance == 0)
    {
        instance=new Settings(parent);
    }
    return instance;
}

Settings::Settings(QObject *parent)
{

}
