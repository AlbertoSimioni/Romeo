#include "testdynamicprotocol.h"

TestDynamicProtocol::TestDynamicProtocol(QObject *parent) :
    QObject(parent){
}



void TestDynamicProtocol::dynamicProtocol(){
    QString algName = "algName";
    QString algDescr = "algDescription";
    QList<algorithms::AbstractAlgorithm::AlgorithmParameter> paramList;
    QList<QString> algParameters;
    int clusterNum = 1;
    QString algDylp = "dylp";
    QString algDyfn = "dyfn";
    algorithms::UserDefinedAlgorithm *myAlg = new algorithms::UserDefinedAlgorithm(paramList,algName,algDescr,algDylp,algDyfn);

    QString protName = "protName";
    QString protDescr = "protDescription";
    QList<romeo::model::protocols::features::AbstractFeature*> feat;
    bool testProtocol = false;

    DynamicProtocol *dp = new DynamicProtocol(protName,protDescr,myAlg,clusterNum,algParameters,feat,testProtocol);
    QCOMPARE(protName,dp->getName());
    QCOMPARE(protDescr,dp->getDescription());
    QCOMPARE(algName,dp->getAlgorithmName());
    QCOMPARE(testProtocol,dp->getTest());
    QCOMPARE(DYNAMIC,dp->getType());
}


//QTEST_MAIN(TestDynamicProtocol)

