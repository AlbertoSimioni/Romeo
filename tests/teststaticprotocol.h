#ifndef TESTSTATICPROTOCOL_H
#define TESTSTATICPROTOCOL_H

#include <QtTest>
//#define private public
#include <../src/romeo/model/protocols/staticprotocol.h>
#include <../src/romeo/model/protocols/algorithms/userdefinedalgorithm.h>

using namespace romeo::model::protocols;

class TestStaticProtocol : public QObject // LCOV_EXCL_LINE
{
    Q_OBJECT

public:
    explicit TestStaticProtocol(QObject *parent = 0);

private slots:
    void staticProtocol();
};


#endif // TESTSTATICPROTOCOL_H
