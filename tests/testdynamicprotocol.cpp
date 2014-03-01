#include "testdynamicprotocol.h"

TestDynamicProtocol::TestDynamicProtocol(QObject *parent) :
    QObject(parent){
}



void TestDynamicProtocol::dynamicProtocol(){
    QString algName = "algName";
    QString algDescr = "algDescription";
    QList<algorithms::AbstractAlgorithm::AlgorithmParameter> paramList;
    QString algDylp = "dylp";
    QString algDyfn = "dyfn";
    algorithms::UserDefinedAlgorithm myAlg(paramList,algName,algDescr,algDylp,algDyfn);

    QString protName = "protName";
    QString protDescr = "protDescription";
    QList<romeo::model::protocols::features::AbstractFeature*> feat;
    bool testProtocol = false;

    DynamicProtocol dp(protName,protDescr,&myAlg,feat,testProtocol);
    QCOMPARE(protName,dp.getName());
    QCOMPARE(protDescr,dp.getDescription());
    QCOMPARE(algName,dp.getAlgorithmName());
    QCOMPARE(testProtocol,dp.getTest());
}


//QTEST_MAIN(TestDynamicProtocol)

