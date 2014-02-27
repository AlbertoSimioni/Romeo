#include <QApplication>
#include <QtTest>
#include "testparametervalueform.h"
#include "testnewfeaturedialog.h"
#include "testnewdatasetdialog.h"
//#include "testnewalgorithmparameterform.h" da PENSARCI
//#include "testprotocoldialog.h" da FIXARE
//#include "testfeatureslistdialog.h" da PENSARE
//#include "testalgorithmslistdialog.h" da PENSARE
//#include "testaddsubjectdialog.h" da PENSARE

int main(int argc, char*argv[]){ //main relativo all'esecuzione dei test
    QApplication a(argc, argv);

    TestParameterValueForm tpvf;
    QTest::qExec(&tpvf);

    TestNewFeatureDialog tnfd;
    QTest::qExec(&tnfd);

    TestNewDatasetDialog tndd;
    QTest::qExec(&tndd);

    //TestNewAlgorithmParameterForm tnapf;
    //QTest::qExec(&tnapf);

    //TestProtocolDialog tpd;
    //QTest::qExec(&tpd);

    //TestFeaturesListDialog tfld;
    //QTest::qExec(&tfld);

    //TestAlgorithmsListDialog tald;
    //QTest::qExec(&tald);

    //TestAddSubjectDialog tasd;
    //QTest::qExec(&tasd);

    return 0;
}
