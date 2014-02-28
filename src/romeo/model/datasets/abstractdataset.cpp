#include "abstractdataset.h"
using namespace romeo::model::datasets;
using namespace romeo::model::protocols;
AbstractDataset::AbstractDataset()
{
}

AbstractDataset::AbstractDataset(QString &n): name(n)
{
}

void AbstractDataset::createNewSubject(QString &name, QString &fileSubject, QString &mask)
{
    subjects.append(this->makeSubject(name, fileSubject, mask));
    emit addedSubject(name,fileSubject,mask);
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

QList<Result*> AbstractDataset::getProtocolResults(const QString & protocol) const
{
    QList<Result*> protocolResults;
    AbstractProtocol* prot=this->getProtocol(protocol);
    if( prot )
    {
        return protocols.value(prot);
    }
    return protocolResults;
}

AbstractProtocol *AbstractDataset::getProtocol(const QString &protocolName) const
{
    QList<AbstractProtocol*> protocolsList=protocols.keys();
    for( int i=0; i<protocolsList.length(); ++i){
        if( protocolsList[i]->getName() == protocolName )
            return protocolsList[i];
    }
    return 0;
}


AbstractSubject* AbstractDataset::getSubject(const QString &subjectName) const
{
    AbstractSubject *subj = 0;
    for(int i = 0; i< subjects.size();i++){
        if(subjects[i]->getName() == subjectName)
            subj = subjects[i];
    }

    return subj;
}


QList<AbstractSubject*> AbstractDataset::getSubjectList()const{
    return subjects;

}

void AbstractDataset::deleteSubject(const QString &subjectName){
    bool subjectFind = false;
    for(int i = 0; i< subjects.size() && !subjectFind;i++){
        if(subjects[i]->getName() == subjectName){
            subjects.removeAt(i);
            subjectFind = true;
        }
    }
    if(subjectFind){
        emit removedSubject(subjectName);
    }

}
