#include <QMessageBox>
#include <QString>
#include <QFile>
#include <QIODevice>
#include <QtXmlPatterns/QXmlResultItems>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include "loader.h"
#include <src/romeo/model/protocols/algorithms/algorithmslist.h>
#include <src/romeo/model/protocols/features/featureslist.h>

using namespace romeo::model::core;
using namespace romeo::model::protocols::algorithms;
using namespace romeo::model::protocols::features;
Loader* Loader::instance=0;
Loader *Loader::getInstance(QObject *parent)
{
    if(instance == 0){
        instance=new Loader(parent);
    }
    return instance;
}

bool Loader::loadAlgorithms(QString algFile, AbstractAlgorithm *algorithmList)
{
    QMessageBox msg3;
    msg3.setText(algFile);
    msg3.exec();
    QFile file(algFile);
    if(QFile::exists(algFile)){
        QMessageBox msg;
        msg.setText("esiste");
        msg.exec();
    }
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        return false;
    }
    QXmlStreamReader reader(&file);
    if(!readStart("algorithms", &reader))
    reader.readNext();
    if(!readStart(QString("algorithms"), &reader))
        ;
    while(!reader.atEnd() && !reader.hasError())
    {
        QXmlStreamReader::TokenType token=reader.readNext();
        if(reader.name() == "algorithm")
        {
            QString name;
            QString description;
            QString dyln;
            QString dyfn;
        }

    }
    file.close();
}

bool Loader::loadFeatures(const QString& featFile, FeaturesList* featureList)
{
    QFile file(featFile);
    QMessageBox msg;
    msg.setText(featFile);
    //msg.exec();
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        return false;
    }
    QXmlStreamReader reader(&file);
    if(!readStart("features", &reader))
    {
        return false;
    }
    else{
        QMessageBox msg;
        msg.setText("ho letto le features!");
        //msg.exec();
    }
    while(!reader.atEnd() && !reader.hasError())
    {
        featureList->addFeature(QString("aaas"), FIRSTORDER);
    }
    file.close();
}
Loader::Loader(QObject* parent): QObject(parent)
{
}

bool Loader::readStart(const QString &startElement, QXmlStreamReader *reader)
{
    if(!reader->atEnd() && !reader->hasError())
    {
        QXmlStreamReader::TokenType token=reader->readNext();
        if(token == QXmlStreamReader::StartDocument)
        {
            token= reader->readNext();
            if(!reader->atEnd() && !reader->hasError())
            {
                if(token == QXmlStreamReader::StartElement) {
                    if(reader->name() == startElement)
                        return true;
                }
            }
        }
    }
    if(reader->hasError()){
        return false;
    }
}
