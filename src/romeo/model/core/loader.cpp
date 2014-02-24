#include <QErrorMessage>
#include <QMessageBox>
#include <QString>
#include <QFile>
#include <QIODevice>
#include <QtXmlPatterns/QXmlQuery>
#include <QtXmlPatterns/QXmlResultItems>
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


void Loader::loadDatabase(QDir &databaseFile, QHash<QString, QDir> &datasetFiles)
{
    QFile file(databaseFile.path());
    if(!file.open(QIODevice::ReadOnly))
    {
        QErrorMessage qerr;
        qerr.showMessage(QString("Errore nell'apertura del file: file non trovato"));
    }


    QXmlQuery query;
    query.bindVariable("fileName", &file);

    query.setQuery("doc($fileName)/romeo/datasets/dataset");

    QXmlResultItems xmlResultItems;
    query.evaluateTo(&xmlResultItems);
    QXmlItem item(xmlResultItems.next());
    int i=1;
        while(!item.isNull()){
            if(item.isAtomicValue()){
                QString s("doc($fileName)/romeo/datasets/dataset[");
                s.append(i);
                s.append("]");
                query.setQuery(s);
            }
            item=xmlResultItems.next();
            ++i;
        }
        file.close();
}



/*
void Loader::parseDatabase()
{

}*/
