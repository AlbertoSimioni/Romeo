#include "testsecondorderfeature.h"

TestSecondOrderFeature::TestSecondOrderFeature(QObject *parent) :
    QObject(parent){
}



void TestSecondOrderFeature::secondOrderFeature(){
    QString name = "name";
    QString descr = "description";
    QString dylp = "dylp";
    QString dyfn = "dyfn";

    SecondOrderFeature *df = new SecondOrderFeature(name,dylp,dyfn,descr);
    QCOMPARE(name,df->getName());
    QCOMPARE(descr,df->getDescription());
    QCOMPARE(dylp,df->getDynamicLibraryPath());
    QCOMPARE(dyfn,df->getDynamicFunctionName());
    QCOMPARE(SECONDORDER,df->getType());
    delete df;
}
