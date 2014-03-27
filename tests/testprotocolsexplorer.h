#ifndef TESTPROTOCOLSEXPLORER_H
#define TESTPROTOCOLSEXPLORER_H

#define private public

#include <QtTest>
#include "../src/romeo/view/mainWindow/protocolsexplorer.h"

using namespace romeo::view::mainWindow;
using namespace romeo::model;

class TestProtocolsExplorer : public QObject
{
    Q_OBJECT

public:
    explicit TestProtocolsExplorer(QObject *parent = 0);

private slots:
    void getSelectedProtocolName();
    void onItemDoubleClicked();
    void associateProtocol();
    void deleteProtocol();
};

#endif // TESTPROTOCOLSEXPLORER_H
