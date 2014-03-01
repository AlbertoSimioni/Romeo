#include "abstractsubject.h"
using namespace romeo::model::datasets;
AbstractSubject::AbstractSubject(QString &n, QString &fileSubject, QString &fileMask):name(n), subject(fileSubject), mask(fileMask) {

}

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


