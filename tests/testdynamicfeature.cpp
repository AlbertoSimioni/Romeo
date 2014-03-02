#include "testdynamicfeature.h"

TestDynamicFeature::TestDynamicFeature(QObject *parent) :
    QObject(parent){
}



void TestDynamicFeature::dynamicFeature(){
    QString name = "name";
    QString descr = "description";
    QString dylp = "dylp";
    QString dyfn = "dyfn";

    DynamicFeature *df = new DynamicFeature(name,dylp,dyfn,descr);
    QCOMPARE(name,df->getName());
    QCOMPARE(descr,df->getDescription());
    QCOMPARE(dylp,df->getDynamicLibraryPath());
    QCOMPARE(dyfn,df->getDynamicFunctionName());
    QCOMPARE(DYNAMIC,df->getType());
}


//QTEST_MAIN(TestDynamicFeature)

