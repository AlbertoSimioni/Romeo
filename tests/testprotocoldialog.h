#ifndef TESTPROTOCOLDIALOG_H
#define TESTPROTOCOLDIALOG_H

#include <QtTest>
#define private public
#include <../src/romeo/view/dialogs/protocoldialog.h>

#include <../src/romeo/model/protocols/algorithms/abstractalgorithm.h>
#include <../src/romeo/view/dialogs/parametervalueform.h>
#include <../src/romeo/model/protocols/algorithms/algorithmslist.h>
#include <../src/romeo/model/protocols/algorithms/userdefinedalgorithm.h>
#include <../src/romeo/model/protocols/features/featureslist.h>
#include <../src/romeo/model/protocols/abstractprotocol.h>
#include <../src/romeo/model/protocols/staticprotocol.h>
#include <../src/romeo/model/protocols/dynamicprotocol.h>

using namespace romeo::view::dialogs;
using namespace romeo::model::protocols::features;
using namespace romeo::model::protocols::algorithms;

class TestProtocolDialog : public QObject
{
    Q_OBJECT

public:
    explicit TestProtocolDialog(QObject *parent = 0);

private slots:
    void protocolDialog();
    void showErrorName();
    void finishButtonClicked();
    void resetForms();
    void reject();
    void nextStep();
    void previousStep();
    void addButtonClicked();
    void removeButtonClicked();
    void fillFeaturesList();
    void changeParametersForm();
    void checkEmpty();
    void checkWindowsSizeGLCM();
    void openExistingProtocol();
    void addFeature();
    void removeFeature();
};


#endif // TESTPROTOCOLDIALOG_H
