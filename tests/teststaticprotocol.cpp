#include "teststaticprotocol.h"

TestStaticProtocol::TestStaticProtocol(QObject *parent) :
    QObject(parent){
}

StaticProtocol* TestStaticProtocol::createProtocol(){
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
    int protWindow = 0;
    int protDistance = 0;

    return new StaticProtocol(protName,protDescr,myAlg,clusterNum,algParameters,feat,testProtocol,protWindow,protDistance);
}

void TestStaticProtocol::staticProtocol(){
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
    int protWindow = 0;
    int protDistance = 0;

    StaticProtocol *sp = new StaticProtocol(protName,protDescr,myAlg,clusterNum,algParameters,feat,testProtocol,protWindow,protDistance);
    QCOMPARE(protName,sp->getName());
    QCOMPARE(protDescr,sp->getDescription());
    QCOMPARE(algName,sp->getAlgorithmName());
    QCOMPARE(testProtocol,sp->getTest());
    QCOMPARE(STATIC,sp->getType());
    QCOMPARE(protWindow,sp->getWindowSize());
    QCOMPARE(protDistance,sp->getDistanceToGlcm());
    QCOMPARE(clusterNum,sp->getNClusters());
    QCOMPARE(algParameters,sp->getAlgorithmParameters());
}

void TestStaticProtocol::setWindowSize(){
    StaticProtocol *sp = createProtocol();
    int protWindow = 5;
    sp->setWindowSize(protWindow);
    QCOMPARE(sp->windowSize,protWindow);
}

void TestStaticProtocol::setDistancetoGLCM(){
    StaticProtocol *sp = createProtocol();
    int protDistance = 5;
    sp->setDistanceToGlcm(protDistance);
    QCOMPARE(sp->distanceToGLCM,protDistance);
}

void TestStaticProtocol::setNClusters(){
    StaticProtocol *sp = createProtocol();
    int clusterNum = 5;
    sp->setNClusters(clusterNum);
    QCOMPARE(clusterNum,sp->nClusters);
}

void TestStaticProtocol::setAlgorithmParameters(){
    StaticProtocol *sp = createProtocol();
    QList<QString> algParameters;
    algParameters.append(QString("param1"));
    algParameters.append(QString("param2"));
    sp->setAlgorithmParameters(algParameters);
    QCOMPARE(algParameters,sp->algorithmParameters);
}

void TestStaticProtocol::getFeaturesName(){
    StaticProtocol *sp = createProtocol();

    QStringList emptyList;
    QCOMPARE(emptyList,sp->getFeaturesName());
}
