/**
* \file abstractdataset.cpp
* \author Matteo Pozza
* \date 2014-02-17
**
* \brief Header della classe AbstractDataset del package romeo::model::datasets
*/

#include "abstractdataset.h"
#include <QStringList>
#include <QDebug>
using namespace romeo::model::datasets;
using namespace romeo::model::protocols;


AbstractDataset::AbstractDataset(QString &n): name(n),stopAnalysis(false),currentProtocol(0)
{
}

AbstractDataset::~AbstractDataset()
{
    QHash<AbstractProtocol*, QList<Result*> >::iterator it=protocols.begin();
    for(; it!= protocols.end(); ++it)
    {
        for(int i=0; i< it.value().length(); ++i)
        {
            delete it.value().at(i); //distruggo i risultati allocati in memoria
        }
        it.value().clear(); //elimino il contenuto della lista dei risultati
    }
    protocols.clear();

    while( !subjects.isEmpty() )
    {
        delete subjects.takeLast();
    }
}

void AbstractDataset::createNewSubject(QString &name, QString &fileSubject, QString &mask)
{
    // controllo la consistenza dei dati inseriti
    QString message = this->checkSubject(fileSubject,mask);
    if(message == "Ok") {
        subjects.append(this->makeSubject(name, fileSubject, mask));
        emit addedSubject(name,fileSubject,mask);
        emit modified(this->getName());
    }
    else
        emit invalidSubject(message);
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

QList<Result *> AbstractDataset::getResultsList(const QString &protocol) const
{
    AbstractProtocol* pro=this->getProtocol(protocol);
    if (pro){
        return protocols.find(pro).value();
    }
    return QList<Result*>();
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
    if(pro)
        emit modified(this->getName());
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
        emit modified(this->getName());
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
    if(matchProtocolName){
        emit protocolsModified();
        emit modified(this->getName());
    }
}


QList<AbstractProtocol*> AbstractDataset::getAssociatedProtocolsList(){
    return protocols.keys();
}

QString AbstractDataset::getTypeString()
{
    InputFormat type=getType();
    QString returnType;
    switch (type) {
    case TYPE2D:
        returnType=QString("TYPE2D");
        break;
    case TYPE2DT:
        returnType=QString("TYPE2DT");
        break;
    case TYPE3D:
        returnType=QString("TYPE3D");
        break;
    case TYPE3DT:
        returnType=QString("TYPE3DT");
        break;
    default:
        break;
    }
    return returnType;
}

void AbstractDataset::associateProtocol(protocols::AbstractProtocol *protocol){

    protocols.insert(protocol,QList<Result*>());
    emit protocolsModified();
    emit modified(this->getName());
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


void AbstractDataset::executeAnalysis(QString protocol, QList<QString> subjects, QString resultsPath, bool saveFeatures, QString exportFormat)
{

    stopAnalysis = false;
    QList<AbstractSubject*> subjectsToAnalyze;
   for(int i = 0; i < subjects.size();i++){
       AbstractSubject* subject =  getSubject(subjects[i]);
       if(subject){
           subjectsToAnalyze.append(subject);
       }
   }

   AbstractProtocol* protocolToExecute = getProtocol(protocol);
   currentProtocol = protocolToExecute;
   connect(protocolToExecute,SIGNAL(featureExtracted(QString)),this,SIGNAL(featureExtracted(QString)));
   connect(protocolToExecute,SIGNAL(algorithmExecuted(QString)),this,SIGNAL(algorithmExecuted(QString)));
    for(int i = 0 ; i < subjectsToAnalyze.size() && !stopAnalysis; i++){
        try {
            protocolToExecute->execute(subjectsToAnalyze[i],resultsPath,saveFeatures,exportFormat);
        }
        // eccezione per itk
        catch (itk::ExceptionObject & e) {
            QString errorMessage = "There were errors trying to read the subject named " + subjectsToAnalyze[i]->getName() + " located in " + subjectsToAnalyze[i]->getSubject() + " or its mask located in " + subjectsToAnalyze[i]->getMask();
            emit analysisProblem(errorMessage);
        }
        // eccezione per opencv
        catch (bool e) {
            QString errorMessage = "There were errors trying to read the subject named " + subjectsToAnalyze[i]->getName() + " located in " + subjectsToAnalyze[i]->getSubject() + " or its mask located in " + subjectsToAnalyze[i]->getMask();
            emit analysisProblem(errorMessage);
        }
    }

   disconnect(protocolToExecute,SIGNAL(featureExtracted(QString)),this,SIGNAL(featureExtracted(QString)));
   disconnect(protocolToExecute,SIGNAL(algorithmExecuted(QString)),this,SIGNAL(algorithmExecuted(QString)));
   if(!stopAnalysis){
       qDebug () <<"SALVO RISULTATO";
       addResult(protocolToExecute,new Result(QDateTime::currentDateTime(),resultsPath));
   }
   currentProtocol = 0;
   emit analysisFinished();
   emit newResults();
   emit modified(this->getName());
}



void AbstractDataset::abortAnalysis(){
    stopAnalysis = true;
    currentProtocol->setStopAnalysis(true);
}

