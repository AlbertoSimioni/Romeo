#include "testabstractdataset.h"

TestAbstractDataset::TestAbstractDataset(QObject *parent) :
    QObject(parent){
}

void TestAbstractDataset::createNewSubject(){
    QString name="NomeDataset";
    QString fileSubject="Subject";
    QString mask="Mask";
    Dataset2D *ds2d=new Dataset2D(name);
    QSignalSpy spyAddSub(ds2d, SIGNAL(addedSubject(QString,QString,QString)));
    QSignalSpy spyMod(ds2d, SIGNAL(modified(QString)));
    ds2d->createNewSubject(name,fileSubject,mask);
    //controlla i segnali emessi
    QCOMPARE(spyAddSub.count(),1);
    QCOMPARE(spyMod.count(),1);
    delete ds2d;
}
/*
void TestAbstractDataset::associateProtocol(){
    QString name="NomeDataset";
    Dataset2D *ds2d=new Dataset2D(name);
    QString nomeP="NomeDataset";
    QString desc="desc";
    romeo::model::protocols::algorithms::AbstractAlgorithm * alg=new romeo::model::protocols::algorithms::FuzzyCMeans();
    int clusterNum=2;
    QList<QString> algParameters=0;
    QList<romeo::model::protocols::features::AbstractFeature*> feat=0 ;
    bool testProtocol=false;
    QSignalSpy spyProtMod(ds2d, SIGNAL(protocolsModified()));
    QSignalSpy spyMod(ds2d, SIGNAL(modified(QString)));
    AbstractProtocol *protocol=new DynamicProtocol(nomeP,desc,alg,clusterNum,algParameters,feat,testProtocol);

    ds2d->associateProtocol(protocol);
    //controlla i segnali emessi
    QCOMPARE(spyProtMod.count(),1);
    QCOMPARE(spyMod.count(),1);
    delete ds2d;
}
*/
void TestAbstractDataset::getName(){
    QString name="name";
    Dataset2D *ds2d=new Dataset2D(name);
    QCOMPARE(ds2d->getName(),name);
    delete ds2d;
}

void TestAbstractDataset::setName(){
    QString name="name";
    Dataset2D *ds2d=new Dataset2D(name);
    QString nameChanged="nameChanged";
    ds2d->setName(nameChanged);
    QCOMPARE(ds2d->getName(),nameChanged);
    delete ds2d;
}

void TestAbstractDataset::getProtocolResults(){
    QString name="name";
    Dataset2D *ds2d=new Dataset2D(name);
    QString protocol="protocol";
    QStringList strList= ds2d->getProtocolResults(protocol);
    QStringList null;
    QList<Result *> strListRes= ds2d->getResultsList(protocol);
    QList<Result *> nullList;
    QCOMPARE(strList,null);
    QCOMPARE(strListRes,nullList);
    delete ds2d;
}

/*
void getTypeString(){
    void TestDataset2D::getProtocolsType_data(){
        QTest::addColumn<romeo::model::protocols::ProtocolType>("Type");

        QTest::newRow("dataset1")<<romeo::model::protocols::STATIC;
    }

    void TestDataset2D::getProtocolsType(){
        QString string ="a";
        Dataset2D *ds2d=new Dataset2D(string);

        QFETCH(romeo::model::protocols::ProtocolType,Type);

        QCOMPARE(ds2d->getProtocolsType(),Type);
        }
}
*/
/*void getSubjectList();
void removeProtocolAssociation();
void getAssociatedProtocolsList();
void addResult();
void getProtocolResults();
void getResultPath();
void getProtocol();
void getProtocolList();
void getSubject();
void deleteSubject();
void executeAnalysis();
*/

//QTEST_MAIN(TestAbstractDataset)

