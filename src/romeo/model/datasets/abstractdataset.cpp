#include "abstractdataset.h"
using namespace romeo::model::datasets;
AbstractDataset::AbstractDataset()
{
}

AbstractDataset::AbstractDataset(QString &n): name(n)
{
}

void AbstractDataset::createNewSubject(QString &name, QString &fileSubject, QString &mask)
{
    subjects.insert(this->makeSubject(name, fileSubject, mask), QList<Result*>());
    return;
}
QString AbstractDataset::getName() const
{
    return name;
}

void AbstractDataset::setName(QString &value)
{
    name = value;
}

QList<Result*> AbstractDataset::getSubjectResults(const QString &subject) const
{
    QList<Result*> subjectResults;
    AbstractSubject* subj=this->getSubject(subject);
    if( subj )
    {
        return subjects.value(subj);
    }
    return subjectResults;
}

AbstractSubject *AbstractDataset::getSubject(const QString &subjectName) const
{
    QList<AbstractSubject*> subjectList=subjects.keys();
    for( int i=0; i<subjectList.length(); ++i){
        if( subjectList[i]->getName() == subjectName )
            return subjectList[i];
    }
    return 0;
}

