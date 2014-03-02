#include "abstractdataset.h"
#include <QStringList>
#include <QDebug>
using namespace romeo::model::datasets;
using namespace romeo::model::protocols;
AbstractDataset::AbstractDataset()
{
}

AbstractDataset::AbstractDataset(QString &n): name(n)
{
}

AbstractDataset::~AbstractDataset()
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

QStringList AbstractDataset::getProtocolResults(const QString & protocol) const
{
    QStringList protocolResults;
    AbstractProtocol* prot=this->getProtocol(protocol);
    QList<Result*> resultsAssociated = protocols.value(prot);
    for(int i = 0; i < resultsAssociated.size(); i++){
        protocolResults.append(resultsAssociated[i]->getExecutionDate().toString());
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

QList<AbstractProtocol *> AbstractDataset::getProtocolList() const
{
    return protocols.keys();
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

void AbstractDataset::addResult(QString protocolName, QString resultPath)
{
    AbstractProtocol* pro=this->getProtocol(protocolName);
    QHash<AbstractProtocol*, QList<Result*> >::iterator it=protocols.find(pro);
    if(it != protocols.end()){//ho trovato un protocollo
        it.value().append(new Result(resultPath));
    }

}


QList<AbstractSubject*> AbstractDataset::getSubjectList()const{
    return subjects;

}

void AbstractDataset::deleteSubject(const QString &subjectName){
    bool subjectFind = false;
    for(int i = 0; i< subjects.size() && !subjectFind;i++){
        if(subjects[i]->getName() == subjectName){
            delete subjects.takeAt(i);
            subjectFind = true;
        }
    }
    if(subjectFind){
        emit removedSubject(subjectName);
    }
}

void AbstractDataset::removeProtocolAssociation(QString protocolName){
    QList<AbstractProtocol*> protocolsList=protocols.keys();
    bool matchProtocolName = false;
    for( int i=0; i<protocolsList.length() && !matchProtocolName; ++i){
        if( protocolsList[i]->getName() == protocolName ){
            matchProtocolName = true;
            QList<Result*> removedResults =protocols.take(protocolsList[i]);
            while(!removedResults.isEmpty()){
                delete removedResults.takeLast();
            }
        }

    }
    if(matchProtocolName) emit protocolsModified();
}


QList<AbstractProtocol*> AbstractDataset::getAssociatedProtocolsList(){
    return protocols.keys();
}

void AbstractDataset::associateProtocol(protocols::AbstractProtocol *protocol){
    protocols.insert(protocol,QList<Result*>());
    emit protocolsModified();
}

void AbstractDataset::addResult(AbstractProtocol* protocol, Result *result){
    QList<Result*> results = protocols.value(protocol);
    results.append(result);
    protocols.insert(protocol,results);
}


QString AbstractDataset::getResultPath(QString protocol, QString resultDate){

    QList<Result*> results = protocols.value(getProtocol(protocol));
    bool findedResult = false;
    QString path;

    for(int i = 0; i < results.size() && !findedResult; i++){
        if(results[i]->getExecutionDate().toString() == resultDate ){
                findedResult = true;
                path = results[i]->getResultPath();
        }
    }
    return path;
}
