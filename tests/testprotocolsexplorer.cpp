#include "testprotocolsexplorer.h"
#include "ui_protocolsexplorer.h"
#include <QPushButton>

TestProtocolsExplorer::TestProtocolsExplorer(QObject *parent) :
    QObject(parent)
{
}

void TestProtocolsExplorer::getSelectedProtocolName(){
    ProtocolsExplorer *pe = new ProtocolsExplorer();

    QCOMPARE(pe->getSelectedProtocolName(),QString());

    delete pe;
}

void TestProtocolsExplorer::onItemDoubleClicked(){
    ProtocolsExplorer *pe = new ProtocolsExplorer();
    QSignalSpy spy(pe,SIGNAL(openProtocol(QString)));

    pe->onItemDoubleClicked();

    QCOMPARE(spy.count(),1);

    delete pe;
}

void TestProtocolsExplorer::associateProtocol(){
    ProtocolsExplorer *pe = new ProtocolsExplorer();
    QSignalSpy spy(pe,SIGNAL(associateProtocol(QString)));

    pe->associateProtocol();

    QCOMPARE(spy.count(),1);
    delete pe;
}

void TestProtocolsExplorer::deleteProtocol(){
    ProtocolsExplorer *pe = new ProtocolsExplorer();
    QSignalSpy spy(pe,SIGNAL(deleteProtocol(QString)));

    pe->deleteProtocol();

    QCOMPARE(spy.count(),1);
    delete pe;
}
