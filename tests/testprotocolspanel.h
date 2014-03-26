#ifndef TESTPROTOCOLSPANEL_H
#define TESTPROTOCOLSPANEL_H

#include <QtTest>
#define private public
#include <../src/romeo/view/mainWindow/protocolspanel.h>

#include <../src/romeo/model/protocols/algorithms/abstractalgorithm.h>
#include <../src/romeo/view/dialogs/parametervalueform.h>
#include <../src/romeo/model/protocols/algorithms/algorithmslist.h>
#include <../src/romeo/model/protocols/algorithms/userdefinedalgorithm.h>
#include <../src/romeo/model/protocols/features/featureslist.h>
#include <../src/romeo/model/protocols/abstractprotocol.h>
#include <../src/romeo/model/protocols/staticprotocol.h>
#include <../src/romeo/model/protocols/dynamicprotocol.h>
#include <../src/romeo/model/datasets/dataset2d.h>

using namespace romeo::view::mainWindow;
using namespace romeo::model::protocols::features;
using namespace romeo::model::protocols::algorithms;
using namespace romeo::model::datasets;

class TestProtocolsPanel : public QObject
{
    Q_OBJECT

public:
    explicit TestProtocolsPanel(QObject *parent = 0);

private slots:
    void fillProtocolsList();
    void changeDescription();
    void addProtocol();
    void onDeleteClicked();
    void getSelectedProtocol();
    void getCurrentDataset();
};


#endif // TESTPROTOCOLSPANEL_H
