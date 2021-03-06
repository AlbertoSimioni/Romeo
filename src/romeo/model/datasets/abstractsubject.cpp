/**
* \file abstractsubject.cpp
* \author Matteo Pozza
* \date 2014-02-17
**
* \brief Header della classe AbstractSubject del package romeo::model::datasets
*/

#include "abstractsubject.h"
using namespace romeo::model::datasets;
AbstractSubject::AbstractSubject(QString &n, QString &fileSubject, QString &fileMask):name(n), subject(fileSubject), mask(fileMask) {

}

AbstractSubject::~AbstractSubject(){}

QString AbstractSubject::getSubject()
{
    return subject;
}

QString AbstractSubject::getMask()
{
    return mask;
}
QString AbstractSubject::getName() const
{
    return name;
}


