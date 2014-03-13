#include "testprotocolslist.h"

TestProtocolsList::TestProtocolsList(QObject *parent) :
    QObject(parent){
}



void TestProtocolsList::getInstance(){
    QCOMPARE(ProtocolsList::getInstance(),ProtocolsList::getInstance());
}

void TestProtocolsList::addRemoveGetProtocol(){
    QString algName = "algName";
    QString algDescr = "algDescription";
    QList<algorithms::AbstractAlgorithm::AlgorithmParameter> paramList;
    QList<QString> algParameters;
    int clusterNum = 1;
    QString algDylp = "dylp";
    QString algDyfn = "dyfn";
    algorithms::UserDefinedAlgorithm *myAlg = new algorithms::UserDefinedAlgorithm(paramList,algName,algDescr,algDylp,algDyfn);

    QString staticProtName = "staticProtName";
    QString staticProtDescr = "staticProtDescription";
    QList<romeo::model::protocols::features::AbstractFeature*> feat;
    bool testStaticProtocol = false;
    int staticProtWindow = 5;
    int staticProtDistance = 2;

    QString dynamicProtName = "dynamicProtName";
    QString dynamicProtDescr = "dynamicProtDescription";
    QList<romeo::model::protocols::features::AbstractFeature*> feat2;
    bool testDynamicProtocol = true;

    ProtocolsList *protList = new ProtocolsList(0);
    QSignalSpy spy(protList,SIGNAL(protocolsListModified()));

    protList->addProtocol(staticProtName,staticProtDescr,myAlg,clusterNum,algParameters,feat,testStaticProtocol,STATIC,staticProtWindow,staticProtDistance);
    QString extractedName = protList->protocolsList.last()->getName();
    QString extractedDescr = protList->protocolsList.last()->getDescription();
    QString extractedAlgName = protList->protocolsList.last()->getAlgorithmName();
    ProtocolType extractedType = protList->protocolsList.last()->getType();
    int extractedWindow = protList->protocolsList.last()->getWindowSize();
    int extractedDistance = protList->protocolsList.last()->getDistanceToGlcm();
    bool extractedTest = protList->protocolsList.last()->getTest();

    QCOMPARE(staticProtName,extractedName);
    QCOMPARE(staticProtDescr,extractedDescr);
    QCOMPARE(myAlg->getName(),extractedAlgName);
    QCOMPARE(STATIC,extractedType);
    QCOMPARE(testStaticProtocol,extractedTest);
    QCOMPARE(staticProtWindow,extractedWindow);
    QCOMPARE(staticProtDistance,extractedDistance);
    QCOMPARE(spy.count(),1);

    protList->addProtocol(dynamicProtName,dynamicProtDescr,myAlg,clusterNum,algParameters,feat2,testDynamicProtocol,DYNAMIC);
    extractedName = protList->protocolsList.last()->getName();
    extractedDescr = protList->protocolsList.last()->getDescription();
    extractedAlgName = protList->protocolsList.last()->getAlgorithmName();
    extractedType = protList->protocolsList.last()->getType();
    extractedWindow = protList->protocolsList.last()->getWindowSize();
    extractedDistance = protList->protocolsList.last()->getDistanceToGlcm();
    extractedTest = protList->protocolsList.last()->getTest();

    QCOMPARE(dynamicProtName,extractedName);
    QCOMPARE(dynamicProtDescr,extractedDescr);
    QCOMPARE(myAlg->getName(),extractedAlgName);
    QCOMPARE(DYNAMIC,extractedType);
    QCOMPARE(testDynamicProtocol,extractedTest);

    QCOMPARE(spy.count(),2);

    AbstractProtocol *abstractStaticPro = protList->getProtocol(staticProtName);
    QVERIFY(abstractStaticPro != 0);

    StaticProtocol *staticProt = dynamic_cast<StaticProtocol*> (abstractStaticPro);

    QCOMPARE(staticProtName,staticProt->getName());
    QCOMPARE(staticProtDescr,staticProt->getDescription());
    QCOMPARE(STATIC,staticProt->getType());
    QCOMPARE(testStaticProtocol,staticProt->getTest());
    QCOMPARE(algName,staticProt->getAlgorithmName());
    QCOMPARE(staticProtWindow,staticProt->getWindowSize());
    QCOMPARE(staticProtDistance,staticProt->getDistanceToGlcm());

    AbstractProtocol *dynamicProt = protList->getProtocol(dynamicProtName);
    QVERIFY(dynamicProt != 0);
    QCOMPARE(dynamicProtName,dynamicProt->getName());
    QCOMPARE(dynamicProtDescr,dynamicProt->getDescription());
    QCOMPARE(DYNAMIC,dynamicProt->getType());
    QCOMPARE(testDynamicProtocol,dynamicProt->getTest());
    QCOMPARE(algName,dynamicProt->getAlgorithmName());

    QString notExistingProtName = "notExistingProtocol";
    AbstractProtocol *notExistingProt = protList->getProtocol(notExistingProtName);
    QVERIFY(notExistingProt == 0);

    protList->removeProtocol(staticProtName);
    QCOMPARE(spy.count(),3);
    QVERIFY(protList->getProtocol(staticProtName) == 0);

    protList->removeProtocol(dynamicProtName);
    QCOMPARE(spy.count(),4);
    QVERIFY(protList->getProtocol(dynamicProtName) == 0);

    protList->removeProtocol(notExistingProtName);
    QCOMPARE(spy.count(),5);
    QVERIFY(protList->getProtocol(notExistingProtName) == 0);

    delete myAlg;
    delete protList;
}
