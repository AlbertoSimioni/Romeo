#include "loader.h"

#include <QXmlStreamReader>
using namespace romeo::model::core;

Loader* Loader::instance=0;
Loader *Loader::getInstance()
{
    if(instance == 0){
        instance=new Loader();
    }
    return instance;
}

void Loader::loadDatabase(QDir &databaseFile, QHash<QString, QDir> &datasetFiles)
{
}

Loader::Loader()
{
}
