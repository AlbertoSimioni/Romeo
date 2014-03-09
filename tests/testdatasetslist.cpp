#include "testdatasetslist.h"

TestDatasetsList::TestDatasetsList(QObject *parent) :
    QObject(parent){
}



void TestDatasetsList::getInstance()
{
    DatasetsList al(0);
    QCOMPARE(al.getInstance(), al.getInstance()); //verifico che per entrambe le chiamate l'istanza restituita sia sempre la stessa
}


void TestDatasetsList::getDataset()
{
    DatasetsList list(0);
    QString dataset1 = "primoDs1";
    QString dataset2 = "primoDs2";

    list.addDataset(dataset1,romeo::model::TYPE2D);

    AbstractDataset *test1=list.getDataset(dataset1);
    AbstractDataset *test2=list.getDataset(dataset2);
    //verifico che il getDataset restituisca il dataset col nome e type giusto
    QCOMPARE(test1->getName(),QString("primoDs1"));
    QCOMPARE(test1->getType(),romeo::model::TYPE2D);
    //test che VERIFICA CHE NON CI SIANO DATASET COL NOME SBAGLIATO
    QVERIFY(test2==0);
}

///da completare verificando i vari casi e i segnali emessi
void TestDatasetsList::addDataset()
{

    QString datasetName = "name";
    romeo::model::InputFormat datasetType = romeo::model::TYPE2D;
      DatasetsList list(0);
    list.addDataset(datasetName,romeo::model::TYPE2D);
    QCOMPARE(datasetName,list.getDataset(datasetName)->getName());
    QCOMPARE(datasetType,list.getDataset(datasetName)->getType());
//controlla il segnale datasetListMOdified
  //  QSignalSpy spy(&list, SIGNAL(datasetsListModified()));
  //  QCOMPARE(spy.count(),1);

}

void TestDatasetsList::getDatasetsList(){
    DatasetsList list(0);
    list.addDataset(QString("primoDS"),romeo::model::TYPE2D);
    list.addDataset(QString("secondoDS"),romeo::model::TYPE2DT);
    list.addDataset(QString("terzoDS"),romeo::model::TYPE3D);
    list.addDataset(QString("quartoDS"),romeo::model::TYPE3DT);

    QList<AbstractDataset*> toTest=list.getDatasetsList();

    QCOMPARE(toTest.at(0)->getName(),QString("primoDS"));
    QCOMPARE(toTest.at(1)->getName(),QString("secondoDS"));
    QCOMPARE(toTest.at(2)->getName(),QString("terzoDS"));
    QCOMPARE(toTest.at(3)->getName(),QString("quartoDS"));

}

void TestDatasetsList::getDatasetsNames(){
    DatasetsList list(0);
    QList<QString> uau=list.getDatasetsNames();
    QCOMPARE(1,1);
}

//DA COMPLETARE
void TestDatasetsList::addDatasetFile(){
    DatasetsList list(0);
    list.addDatasetFile(QString("testFile"));

}

void TestDatasetsList::getNextDataset(){
    DatasetsList list(0);
    QString AbsDSTEst="AbsDSTEst";
    AbstractDataset *abstrPrewDs=new Dataset2D(AbsDSTEst);
    AbstractDataset *abstrDs=list.getNextDataset(abstrPrewDs);

    delete abstrPrewDs;
}

void TestDatasetsList::deleteDataset(){
    DatasetsList list(0);
    QString AbsDSTEst="AbsDSTEst";
    AbstractDataset *abstrPrewDs=new Dataset2D(AbsDSTEst);
    list.deleteDataset(abstrPrewDs);


        delete abstrPrewDs;
}

void TestDatasetsList::deleteProtocolAssociations(){
    DatasetsList list(0);
    list.deleteProtocolAssociations(QString("ProtAss"));

}

//QTEST_MAIN(TestDatasetsList)

