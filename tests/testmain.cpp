#include <QApplication>
#include <QtTest>
#include "testparametervalueform.h"
#include "testnewfeaturedialog.h"
#include "testnewdatasetdialog.h"
#include "testprotocoldialog.h"
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
#include "testcontroller.h"
#include "testdataset2d.h"
#include "testdataset2dt.h"
#include "testdataset3d.h"
#include "testdataset3dt.h"
#include "testsubject2d.h"
#include "testsubject2dt.h"
#include "testsubject3d.h"
#include "testsubject3dt.h"
#include "testresult.h"
#include "testdatasetslist.h"
#include "testabstractsubject.h"
#include "testabstractdataset.h"
#include "testexecutedialog.h"

int main(int argc, char*argv[]){ //main relativo all'esecuzione dei test
    QApplication a(argc, argv);

    TestParameterValueForm tpvf;
    QTest::qExec(&tpvf);

    TestNewFeatureDialog tnfd;
    QTest::qExec(&tnfd);

    TestNewDatasetDialog tndd;
    QTest::qExec(&tndd);

    TestProtocolDialog tpd;
    QTest::qExec(&tpd);

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

    TestDataset2D tds2d;
    QTest::qExec(&tds2d);

    TestDataset2DT tds2dt;
    QTest::qExec(&tds2dt);

    TestDataset3D tds3d;
    QTest::qExec(&tds3d);

    TestDataset3DT tds3dt;
    QTest::qExec(&tds3dt);

    TestSubject2D ts2d;
    QTest::qExec(&ts2d);

    TestSubject2DT ts2dt;
    QTest::qExec(&ts2dt);

    TestSubject3D ts3d;
    QTest::qExec(&ts3d);

    TestSubject3DT ts3dt;
    QTest::qExec(&ts3dt);

    TestResult tres;
    QTest::qExec(&tres);

    TestDatasetsList tdsL;
    QTest::qExec(&tdsL);

    TestController tc;
    QTest::qExec(&tc);

    TestAbstractSubject taS;
    QTest::qExec(&taS);

    TestAbstractDataset tads;
    QTest::qExec(&tads);

    TestExecuteDialog ted;
    QTest::qExec(&ted);

    return 0;
}
