#include "testdynamicprotocol.h"

TestDynamicProtocol::TestDynamicProtocol(QObject *parent) :
    QObject(parent){
}


DynamicProtocol* TestDynamicProtocol::createProtocol(){
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

    return new DynamicProtocol(protName,protDescr,myAlg,clusterNum,algParameters,feat,testProtocol);
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
    QCOMPARE(clusterNum,dp->getNClusters());
    QCOMPARE(algParameters,dp->getAlgorithmParameters());
}

void TestDynamicProtocol::setNClusters(){
    DynamicProtocol *dp = createProtocol();
    int clusterNum = 5;
    dp->setNClusters(clusterNum);
    QCOMPARE(clusterNum,dp->nClusters);
}

void TestDynamicProtocol::setAlgorithmParameters(){
    DynamicProtocol *dp = createProtocol();
    QList<QString> algParameters;
    algParameters.append(QString("param1"));
    algParameters.append(QString("param2"));
    dp->setAlgorithmParameters(algParameters);
    QCOMPARE(algParameters,dp->algorithmParameters);
}

void TestDynamicProtocol::getFeaturesName(){
    DynamicProtocol *dp = createProtocol();
    /*QList<romeo::model::protocols::features::AbstractFeature*> feat;

    QString name = "myfeat";
    QString descr = "description";
    QString dylp = "dylp";
    QString dyfn = "dyfn";
    romeo::model::protocols::features::FirstOrderFeature *df = new romeo::model::protocols::features::FirstOrderFeature(name,dylp,dyfn,descr);

    feat.append(df);
    QStringList list;
    list.append(QString("myfeat"));
    dp->setFeatures(feat);
    QCOMPARE(list,dp->getFeaturesName());*/

    QStringList emptyList;
    QCOMPARE(emptyList,dp->getFeaturesName());
}


//QTEST_MAIN(TestDynamicProtocol)

