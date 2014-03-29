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
#include "testnewalgorithmdialog.h"
#include "testnewalgorithmparameterform.h"
#include "testaddsubjectdialog.h"
#include "testprotocolspanel.h"
#include "testcontroller.h"
#include "testprotocolscontroller.h"
#include "testfeaturescontroller.h"
#include "testalgorithmscontroller.h"
#include "testcolor.h"
#include "testexecutepanel.h"
#include "testfilesystemexplorer.h"
#include "testprotocolsexplorer.h"
#include "testmainwindow.h"
#include "testfeatureslistdialog.h"
#include "testsubjectspanel.h"

int main(int argc, char*argv[]){ //main relativo all'esecuzione dei test
    QApplication a(argc, argv);

    TestParameterValueForm tpvf;

    TestNewFeatureDialog tnfd;

    TestNewDatasetDialog tndd;

    TestProtocolDialog tpd;

    TestAbstractAlgorithm taa;

    TestAlgorithmsList taa2;

    TestStaticProtocol tsp;

    TestProtocolsList tpl;

    TestDynamicFeature tdf;

    TestFirstOrderFeature tdof;

    TestSecondOrderFeature tsof;

    TestFeaturesList tfl;

    TestWriter tw;

    TestUserDefinedAlgorithm tuda;

    TestDataset2D tds2d;

    TestDataset3DT tds3dt;

    TestSubject2D ts2d;

    TestSubject2DT ts2dt;

    TestSubject3D ts3d;

    TestSubject3DT ts3dt;

    TestResult tres;

    TestDatasetsList tdsL;

    TestAbstractSubject taS;

    TestExecuteDialog ted;

    TestNewAlgorithmDialog tnad;

    TestNewAlgorithmParameterForm tnapf;

    TestAddSubjectDialog tasd;

    TestProtocolsPanel tpp;

    TestDatasetsController tdc;

    TestProtocolsController tpc;

    TestFeaturesController tfc;

    TestAlgorithmsController tac;

    TestColor tc;

    TestExecutePanel tep;

    TestFileSystemExplorer tfse;

    TestProtocolsExplorer tpe;

    TestMainWindow tmw;

    TestDataset3D tds3d;

    TestDynamicProtocol tdp;

    TestFeaturesListDialog tfld;

    TestDataset2DT tds2dt;

    TestSubjectsPanel tsp2;

    TestAbstractDataset tads;


    return  QTest::qExec(&tpvf) | QTest::qExec(&tnfd) |
            QTest::qExec(&tndd) | QTest::qExec(&tpd) | QTest::qExec(&taa) | QTest::qExec(&taa2) |
            QTest::qExec(&tsp) | QTest::qExec(&tpl) | QTest::qExec(&tdf) | QTest::qExec(&tdof) |
            QTest::qExec(&tsof) | QTest::qExec(&tfl) | QTest::qExec(&tw) | QTest::qExec(&tuda) |
            QTest::qExec(&tds2d) | QTest::qExec(&tds3dt) | QTest::qExec(&ts2d) | QTest::qExec(&ts2dt) |
            QTest::qExec(&ts3d)| QTest::qExec(&ts3dt) | QTest::qExec(&tres) | QTest::qExec(&tdsL) |
            QTest::qExec(&taS) | QTest::qExec(&ted) | QTest::qExec(&tnad) | QTest::qExec(&tnapf) |
            QTest::qExec(&tasd) | QTest::qExec(&tpp) | QTest::qExec(&tdc) | QTest::qExec(&tpc) |
            QTest::qExec(&tfc) | QTest::qExec(&tac) | QTest::qExec(&tc) | QTest::qExec(&tep) | QTest::qExec(&tfse) |
            QTest::qExec(&tpe) | QTest::qExec(&tmw) | QTest::qExec(&tds3d) | QTest::qExec(&tdp) |
            QTest::qExec(&tfld) | QTest::qExec(&tds2dt) | QTest::qExec(&tsp2) | QTest::qExec(&tads);
}
