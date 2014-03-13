#include "testuserdefinedalgorithm.h"

TestUserDefinedAlgorithm::TestUserDefinedAlgorithm(QObject *parent) :
    QObject(parent){
}

void TestUserDefinedAlgorithm::getDynamicLibraryPath()
{
    QString algName = "name";
    QString algDescr = "description";
    QList<AbstractAlgorithm::AlgorithmParameter> paramList;
    QString algDylp = "dylp";
    QString algDyfn = "dyfn";
    UserDefinedAlgorithm *myAlg = new UserDefinedAlgorithm(paramList,algName,algDescr,algDylp,algDyfn);

    QCOMPARE(algName,myAlg->getName());
    QCOMPARE(algDescr,myAlg->getDescription());
    QCOMPARE(algDylp,myAlg->getDynamicLibraryPath());
    QCOMPARE(algDyfn,myAlg->getDynamicFunctionName());
    delete myAlg;
}

void TestUserDefinedAlgorithm::getDynamicFunctionName(){
    QString algName = "name";
    QString algDescr = "description";
    QList<AbstractAlgorithm::AlgorithmParameter> paramList;
    QString algDylp = "dylp";
    QString algDyfn = "dyfn";
    UserDefinedAlgorithm *myAlg = new UserDefinedAlgorithm(paramList,algName,algDescr,algDylp,algDyfn);

    QCOMPARE(algName,myAlg->getName());
    QCOMPARE(algDescr,myAlg->getDescription());
    QCOMPARE(algDylp,myAlg->getDynamicLibraryPath());
    QCOMPARE(algDyfn,myAlg->getDynamicFunctionName());
    delete myAlg;
}
