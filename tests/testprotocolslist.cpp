#include "testprotocolslist.h"

TestProtocolsList::TestProtocolsList(QObject *parent) :
    QObject(parent){
}



void TestProtocolsList::getInstance(){
    ProtocolsList *protList = new ProtocolsList(0);
    QCOMPARE(protList->getInstance(0),protList->getInstance(0));
    ProtocolsList *protList2 = new ProtocolsList(0);
    QCOMPARE(protList2->getInstance(0),protList2->getInstance(protList));
    ProtocolsList *protList3 = new ProtocolsList(0);
    QCOMPARE(protList3->getInstance(protList),protList3->getInstance(0));
}


void TestProtocolsList::addRemoveGetProtocol(){
    QString algName = "algName";
    QString algDescr = "algDescription";
    QList<algorithms::AbstractAlgorithm::AlgorithmParameter> paramList;
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

    protList->addProtocol(staticProtName,staticProtDescr,myAlg,feat,testStaticProtocol,STATIC,staticProtWindow,staticProtDistance);

    QCOMPARE(spy.count(),1);

    protList->addProtocol(dynamicProtName,dynamicProtDescr,myAlg,feat2,testDynamicProtocol,DYNAMIC);

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
}



//QTEST_MAIN(TestProtocolsList)
