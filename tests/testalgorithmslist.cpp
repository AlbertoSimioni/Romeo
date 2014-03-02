#include "testalgorithmslist.h"

TestAlgorithmsList::TestAlgorithmsList(QObject *parent) :
    QObject(parent){
}



void TestAlgorithmsList::getInstance()
{
    AlgorithmsList al(0);
    QCOMPARE(al.getInstance(), al.getInstance()); //verifico che per entrambe le chiamate l'istanza restituita sia sempre la stessa
}


void TestAlgorithmsList::getAlgorithm()
{
    AlgorithmsList list(0);
    QString algName = "name";
    QString algDescr = "description";
    QList<AbstractAlgorithm::AlgorithmParameter> paramList;
    QString algDylp = "dylp";
    QString algDyfn = "dyfn";
    UserDefinedAlgorithm *myAlg = new UserDefinedAlgorithm(paramList,algName,algDescr,algDylp,algDyfn);

    list.addAlgorithm(myAlg);
    AbstractAlgorithm *expectedAlg = list.getAlgorithmsList().last(); //estraggo l'algoritmo appena aggiunto

    AbstractAlgorithm *extractedAlg = list.getAlgorithm(algName); //estraggo l'algoritmo con nome algName

    QCOMPARE(expectedAlg,extractedAlg); //verifico che i due algoritmi coincidano, e che quindi i metodi funzionino
}


void TestAlgorithmsList::addAlgorithm()
{
    AlgorithmsList list(0);
    QString algName = "name";
    if(!list.getAlgorithm(algName)){
        QString algDescr = "description";
        QList<AbstractAlgorithm::AlgorithmParameter> paramList;
        QString algDylp = "dylp";
        QString algDyfn = "dyfn";

        QSignalSpy spy(&list, SIGNAL(algorithmsListModified())); //controlla i segnali emessi

        list.addAlgorithm(algName,algDescr,paramList,algDylp,algDyfn);
        AbstractAlgorithm *extractedAlg = list.getAlgorithmsList().last(); //estraggo l'algoritmo appena aggiunto e controllo i suoi attributi

        QCOMPARE(algName,extractedAlg->getName());
        QCOMPARE(algDescr,extractedAlg->getDescription());
        QCOMPARE(QTest::toString(paramList),QTest::toString(extractedAlg->getParameters()));

        QCOMPARE(spy.count(),1);
    }
}


void TestAlgorithmsList::addAlgorithmByCopy(){
    AlgorithmsList list(0);
    QString algName = "name";
    if(!list.getAlgorithm(algName)){
        QString algDescr = "description";
        QList<AbstractAlgorithm::AlgorithmParameter> paramList;
        QString algDylp = "dylp";
        QString algDyfn = "dyfn";
        UserDefinedAlgorithm *myAlg = new UserDefinedAlgorithm(paramList,algName,algDescr,algDylp,algDyfn);
        QSignalSpy spy(&list, SIGNAL(algorithmsListModified())); //controlla i segnali emessi

        list.addAlgorithm(myAlg); //aggiungo l'algoritmo alla lista tramite copia
        AbstractAlgorithm *extractedAlg = list.getAlgorithmsList().last(); //estraggo l'algoritmo appena aggiunto e controllo i suoi attributi

        QCOMPARE(algName,extractedAlg->getName());
        QCOMPARE(algDescr,extractedAlg->getDescription());
        QCOMPARE(QTest::toString(paramList),QTest::toString(extractedAlg->getParameters()));

        QCOMPARE(spy.count(),1);
    }
}


//QTEST_MAIN(TestAlgorithmsList)

