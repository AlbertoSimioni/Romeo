#include "testfirstorderfeature.h"

TestFirstOrderFeature::TestFirstOrderFeature(QObject *parent) :
    QObject(parent){
}



void TestFirstOrderFeature::firstorderFeature(){
    QString name = "name";
    QString descr = "description";
    QString dylp = "dylp";
    QString dyfn = "dyfn";

    FirstOrderFeature *df = new FirstOrderFeature(name,dylp,dyfn,descr);
    QCOMPARE(name,df->getName());
    QCOMPARE(descr,df->getDescription());
    QCOMPARE(dylp,df->getDynamicLibraryPath());
    QCOMPARE(dyfn,df->getDynamicFunctionName());
    QCOMPARE(FIRSTORDER,df->getType());
    delete df;
}
