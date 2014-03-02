#include "teststaticprotocol.h"

TestStaticProtocol::TestStaticProtocol(QObject *parent) :
    QObject(parent){
}


void TestStaticProtocol::staticProtocol(){
    QString algName = "algName";
    QString algDescr = "algDescription";
    QList<algorithms::AbstractAlgorithm::AlgorithmParameter> paramList;
    QString algDylp = "dylp";
    QString algDyfn = "dyfn";
    algorithms::UserDefinedAlgorithm *myAlg = new algorithms::UserDefinedAlgorithm(paramList,algName,algDescr,algDylp,algDyfn);

    QString protName = "protName";
    QString protDescr = "protDescription";
    QList<romeo::model::protocols::features::AbstractFeature*> feat;
    bool testProtocol = false;
    int protWindow = 0;
    int protDistance = 0;

    StaticProtocol *dp = new StaticProtocol(protName,protDescr,myAlg,feat,testProtocol,protWindow,protDistance);
    QCOMPARE(protName,dp->getName());
    QCOMPARE(protDescr,dp->getDescription());
    QCOMPARE(algName,dp->getAlgorithmName());
    QCOMPARE(testProtocol,dp->getTest());
    QCOMPARE(STATIC,dp->getType());
    QCOMPARE(protWindow,dp->getWindowSize());
    QCOMPARE(protDistance,dp->getDistanceToGlcm());
}


//QTEST_MAIN(TestStaticProtocol)
