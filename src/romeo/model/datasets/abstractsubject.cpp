#include "abstractsubject.h"
using namespace romeo::model::datasets;
AbstractSubject::AbstractSubject(QString &n, QString &fileSubject, QString &fileMask):name(n){

}

QString AbstractSubject::getSubject()
{
    return subject;
}

QString AbstractSubject::getMask()
{
    return mask;
}