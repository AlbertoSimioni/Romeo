#include <QErrorMessage>
#include <QMessageBox>
#include <QString>
#include <QFile>
#include <QIODevice>
#include <QtXmlPatterns/QXmlQuery>
#include <QtXmlPatterns/QXmlResultItems>
#include "loader.h"
#include <src/romeo/model/protocols/algorithms/abstractalgorithm.h>

using namespace romeo::model::core;

Loader* Loader::instance=0;
Loader *Loader::getInstance()
{
    if(instance == 0){
        instance=new Loader();
    }
    return instance;
}

bool Loader::loadAlgorithms(QString algFile)
{
    QFile file(algFile);
    if(!file.open(QIODevice::ReadOnly))
    {
        return false;
    }

    QXmlQuery query;
    query.bindVariable("fileName", &file);

    query.setQuery("doc($fileName)/algorithms/algorithm/name");

    QXmlResultItems xmlResultItems;
    query.evaluateTo(&xmlResultItems);
    QXmlItem item(xmlResultItems.next());
    int i=1;

        while(!item.isNull()){
            QString s(item.toAtomicValue().toString());
            QMessageBox msg;
            msg.setText(s);
            msg.exec();
            item=xmlResultItems.next();
            ++i;
        }
        file.close();
}
Loader::Loader()
{
}
