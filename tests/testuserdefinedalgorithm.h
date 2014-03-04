#ifndef TESTUSERDEFINEDALGORITHM_H
#define TESTUSERDEFINEDALGORITHM_H

#include <QtTest>
//#define private public
#include <../src/romeo/model/protocols/algorithms/userdefinedalgorithm.h>

using namespace romeo::model::protocols::algorithms;

class TestUserDefinedAlgorithm : public QObject
{
    Q_OBJECT

public:
    explicit TestUserDefinedAlgorithm(QObject *parent = 0);

private slots:
    void getDynamicLibraryPath();
    void getDynamicFunctionName();
};


#endif // TESTUSERDEFINEDALGORITHM_H
