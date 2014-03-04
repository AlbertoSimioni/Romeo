#include "testfeatureslist.h"

TestFeaturesList::TestFeaturesList(QObject *parent) :
    QObject(parent){
}



void TestFeaturesList::getInstance(){
    FeaturesList *featList = new FeaturesList(0);
    QCOMPARE(featList->getInstance(0),featList->getInstance(0));
    FeaturesList *featList2 = new FeaturesList(0);
    QCOMPARE(featList2->getInstance(0),featList2->getInstance(featList));
    FeaturesList *featList3 = new FeaturesList(0);
    QCOMPARE(featList3->getInstance(featList),featList3->getInstance(0));
}


void TestFeaturesList::getFeature_data(){
    QTest::addColumn<QString>("featName");
    QTest::addColumn<QString>("featDescr");
    QTest::addColumn<QString>("featDylp");
    QTest::addColumn<QString>("featDyfn");
    QTest::addColumn<FeatureType>("featType");

    QTest::newRow("FirstOrderFeature") << "foname" << "fodescription"<< "fodylp"<< "fodyfn"<< FIRSTORDER;
    QTest::newRow("SecondOrderFeature") << "soname" << "sodescription"<< "sodylp"<< "sodyfn"<< SECONDORDER;
    QTest::newRow("DynamicFeature") << "dynname" << "dyndescription"<< "dyndylp"<< "dyndyfn"<< DYNAMIC;
}


void TestFeaturesList::getFeature()
{
    FeaturesList list(0);
    QFETCH(QString,featName);
        QFETCH(QString,featDescr);
        QFETCH(QString,featDylp);
        QFETCH(QString,featDyfn);
        QFETCH(FeatureType,featType);
        AbstractFeature *feat;

        if(featType==FIRSTORDER)
            feat = new FirstOrderFeature(featName,featDylp,featDyfn,featDescr);

        if(featType==SECONDORDER)
            feat = new SecondOrderFeature(featName,featDylp,featDyfn,featDescr);

        if(featType==DYNAMIC)
            feat = new DynamicFeature(featName,featDylp,featDyfn,featDescr);

    list.addFeature(feat);
    AbstractFeature *expectedFeat = list.getFeaturesList().last();

    AbstractFeature *extractedFeat = list.getFeature(featName);

    QCOMPARE(expectedFeat,extractedFeat);
}


void TestFeaturesList::addFeature_data()
{
    QTest::addColumn<QString>("featName");
    QTest::addColumn<QString>("featDescr");
    QTest::addColumn<QString>("featDylp");
    QTest::addColumn<QString>("featDyfn");
    QTest::addColumn<FeatureType>("featType");

    QTest::newRow("FirstOrderFeature") << "foname" << "fodescription"<< "fodylp"<< "fodyfn"<< FIRSTORDER;
    QTest::newRow("SecondOrderFeature") << "soname" << "sodescription"<< "sodylp"<< "sodyfn"<< SECONDORDER;
    QTest::newRow("DynamicFeature") << "dynname" << "dyndescription"<< "dyndylp"<< "dyndyfn"<< DYNAMIC;
}


void TestFeaturesList::addFeature()
{
    FeaturesList list(0);
    QFETCH(QString,featName);
    if(!list.getFeature(featName)){
        QFETCH(QString,featDescr);
        QFETCH(QString,featDylp);
        QFETCH(QString,featDyfn);
        QFETCH(FeatureType,featType);

        QSignalSpy spy(&list, SIGNAL(featuresListModified())); //controlla i segnali emessi

        list.addFeature(featName,featType,featDescr,featDylp,featDyfn);
        AbstractFeature *extractedFeat = list.getFeaturesList().last(); //estraggo l'algoritmo appena aggiunto e controllo i suoi attributi

        QCOMPARE(featName,extractedFeat->getName());
        QCOMPARE(featDescr,extractedFeat->getDescription());
        QCOMPARE(featDylp,extractedFeat->getDynamicLibraryPath());
        QCOMPARE(featDyfn,extractedFeat->getDynamicFunctionName());
        QCOMPARE(featType,extractedFeat->getType());
        QVERIFY(spy.count()<4);
    }
}

void TestFeaturesList::addFeatureByCopy_data(){
    QTest::addColumn<QString>("featName");
    QTest::addColumn<QString>("featDescr");
    QTest::addColumn<QString>("featDylp");
    QTest::addColumn<QString>("featDyfn");
    QTest::addColumn<FeatureType>("featType");

    QTest::newRow("FirstOrderFeature") << "foname" << "fodescription"<< "fodylp"<< "fodyfn"<< FIRSTORDER;
    QTest::newRow("SecondOrderFeature") << "soname" << "sodescription"<< "sodylp"<< "sodyfn"<< SECONDORDER;
    QTest::newRow("DynamicFeature") << "dynname" << "dyndescription"<< "dyndylp"<< "dyndyfn"<< DYNAMIC;
}


void TestFeaturesList::addFeatureByCopy(){
    FeaturesList list(0);
    QFETCH(QString,featName);
    if(!list.getFeature(featName)){
        QFETCH(QString,featDescr);
        QFETCH(QString,featDylp);
        QFETCH(QString,featDyfn);
        QFETCH(FeatureType,featType);
        AbstractFeature *feat;

        if(featType==FIRSTORDER)
            feat = new FirstOrderFeature(featName,featDylp,featDyfn,featDescr);

        if(featType==SECONDORDER)
            feat = new SecondOrderFeature(featName,featDylp,featDyfn,featDescr);

        if(featType==DYNAMIC)
            feat = new DynamicFeature(featName,featDylp,featDyfn,featDescr);


        QSignalSpy spy(&list, SIGNAL(featuresListModified())); //controlla i segnali emessi

        list.addFeature(feat);
        AbstractFeature *extractedFeat = list.getFeaturesList().last(); //estraggo l'algoritmo appena aggiunto e controllo i suoi attributi

        QCOMPARE(featName,extractedFeat->getName());
        QCOMPARE(featDescr,extractedFeat->getDescription());
        QCOMPARE(featDylp,extractedFeat->getDynamicLibraryPath());
        QCOMPARE(featDyfn,extractedFeat->getDynamicFunctionName());
        QCOMPARE(featType,extractedFeat->getType());
        QVERIFY(spy.count()<4);
    }
}


//QTEST_MAIN(TestFeaturesList)
