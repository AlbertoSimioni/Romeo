#include <QApplication>
#include <QtTest>
#include "testparametervalueform.h"
#include "testnewfeaturedialog.h"
#include "testnewdatasetdialog.h"
//#include "testnewalgorithmparameterform.h" da PENSARCI
#include "testprotocoldialog.h"
//#include "testfeatureslistdialog.h" da PENSARE
//#include "testalgorithmslistdialog.h" da PENSARE
//#include "testaddsubjectdialog.h" da PENSARE

#include "testabstractalgorithm.h"
#include "testalgorithmslist.h"
#include "testdynamicprotocol.h"
#include "teststaticprotocol.h"
#include "testprotocolslist.h"
#include "testdynamicfeature.h"
#include "testfirstorderfeature.h"
#include "testsecondorderfeature.h"
#include "testfeatureslist.h"
#include "testwriter.h"
#include "testuserdefinedalgorithm.h"

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

    TestProtocolDialog tpd;
    QTest::qExec(&tpd);

    //TestFeaturesListDialog tfld;
    //QTest::qExec(&tfld);

    //TestAlgorithmsListDialog tald;
    //QTest::qExec(&tald);

    //TestAddSubjectDialog tasd;
    //QTest::qExec(&tasd);

    TestAbstractAlgorithm taa;
    QTest::qExec(&taa);

    TestAlgorithmsList taa2;
    QTest::qExec(&taa2);

    TestDynamicProtocol tdp;
    QTest::qExec(&tdp);

    TestStaticProtocol tsp;
    QTest::qExec(&tsp);

    TestProtocolsList tpl;
    QTest::qExec(&tpl);

    TestDynamicFeature tdf;
    QTest::qExec(&tdf);

    TestFirstOrderFeature tdof;
    QTest::qExec(&tdof);

    TestSecondOrderFeature tsof;
    QTest::qExec(&tsof);

    TestFeaturesList tfl;
    QTest::qExec(&tfl);

    TestWriter tw;
    QTest::qExec(&tw);

    TestUserDefinedAlgorithm tuda;
    QTest::qExec(&tuda);

    return 0;
}
