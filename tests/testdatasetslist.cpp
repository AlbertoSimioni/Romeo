#include "testdatasetslist.h"

TestDatasetsList::TestDatasetsList(QObject *parent) :
    QObject(parent){
}



void TestDatasetsList::getInstance()
{
    QCOMPARE(DatasetsList::getInstance(), DatasetsList::getInstance()); //verifico che per entrambe le chiamate l'istanza restituita sia sempre la stessa
}


void TestDatasetsList::getDataset()
{
    DatasetsList *list = new DatasetsList();
    QString dataset1 = "primoDs1";
    QString dataset2 = "primoDs2";

    list->addDataset(dataset1,romeo::model::TYPE2D);

    AbstractDataset *test1=list->getDataset(dataset1);
    AbstractDataset *test2=list->getDataset(dataset2);
    //verifico che il getDataset restituisca il dataset con nome e type giusto
    QCOMPARE(test1->getName(),QString("primoDs1"));
    QCOMPARE(test1->getType(),romeo::model::TYPE2D);
    //test che verifica che non ci siano dataset col nome sbagliato
    QVERIFY(test2==0);
}


void TestDatasetsList::addDataset()
{

    QString datasetName = "name";
    romeo::model::InputFormat datasetType = romeo::model::TYPE2D;
    DatasetsList *list = new DatasetsList();
    QSignalSpy spy(list, SIGNAL(datasetsListModified()));
    list->addDataset(datasetName,romeo::model::TYPE2D);
    QCOMPARE(datasetName,list->getDataset(datasetName)->getName());
    QCOMPARE(datasetType,list->getDataset(datasetName)->getType());
    QCOMPARE(spy.count(),1);
}

void TestDatasetsList::getDatasetsList(){
    DatasetsList *list = new DatasetsList();
    list->addDataset(QString("primoDS"),romeo::model::TYPE2D);
    list->addDataset(QString("secondoDS"),romeo::model::TYPE2DT);
    list->addDataset(QString("terzoDS"),romeo::model::TYPE3D);
    list->addDataset(QString("quartoDS"),romeo::model::TYPE3DT);

    QList<AbstractDataset*> toTest=list->getDatasetsList();

    QCOMPARE(toTest.at(0)->getName(),QString("primoDS"));
    QCOMPARE(toTest.at(1)->getName(),QString("secondoDS"));
    QCOMPARE(toTest.at(2)->getName(),QString("terzoDS"));
    QCOMPARE(toTest.at(3)->getName(),QString("quartoDS"));

}

void TestDatasetsList::getDatasetsNames(){
    DatasetsList *list = new DatasetsList();
    QList<QString> datasetsNames=list->getDatasetsNames();
    QCOMPARE(datasetsNames.isEmpty(),true);
    delete list;
}


void TestDatasetsList::addDatasetFile(){
    DatasetsList *list = new DatasetsList();
    QSignalSpy spy(list,SIGNAL(datasetsListModified()));
    list->addDatasetFile(QString("testFile"));
    QCOMPARE(spy.count(),1);
    delete list;
}

void TestDatasetsList::getNextDataset(){
    DatasetsList *list = new DatasetsList();
    QString datasetName="dataset";
    AbstractDataset *myDataset=new Dataset2D(datasetName);
    AbstractDataset *abstrDs=list->getNextDataset(myDataset);
    AbstractDataset *expected = 0;
    QCOMPARE(abstrDs,expected);
    delete myDataset;
    delete list;
}

void TestDatasetsList::deleteDataset(){
    DatasetsList *list = new DatasetsList();
    QSignalSpy spy(list,SIGNAL(datasetsListModified()));
    QString datasetName="dataset";
    AbstractDataset *myDataset=new Dataset2D(datasetName);
    list->addDataset(datasetName,romeo::model::TYPE2D);
    list->deleteDataset(myDataset);
    QCOMPARE(spy.count(),1);
    delete myDataset;
    delete list;
}

void TestDatasetsList::deleteProtocolAssociations(){
    DatasetsList *list = new DatasetsList();
    QSignalSpy spy(list,SIGNAL(datasetsListModified()));
    list->deleteProtocolAssociations(QString("ProtAss"));
    QCOMPARE(spy.count(),0);
    delete list;
}
