#ifndef TESTDYNAMICPROTOCOL_H
#define TESTDYNAMICPROTOCOL_H

#include <QtTest>
//#define private public
#include <../src/romeo/model/protocols/dynamicprotocol.h>
#include <../src/romeo/model/protocols/algorithms/userdefinedalgorithm.h>

using namespace romeo::model::protocols;

class TestDynamicProtocol : public QObject
{
    Q_OBJECT

public:
    explicit TestDynamicProtocol(QObject *parent = 0);

private slots:
    void dynamicProtocol();
};


#endif // TESTDYNAMICPROTOCOL_H
