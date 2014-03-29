#ifndef TESTALGORITHMSCONTROLLER_H
#define TESTALGORITHMSCONTROLLER_H

#include <QtTest>
#define private public
#include <../src/romeo/controller/controller.h>
#include <../src/romeo/controller/algorithmscontroller.h>
#include <../src/romeo/model/protocols/algorithms/algorithmslist.h>
#include <../src/romeo/model/protocols/algorithms/userdefinedalgorithm.h>

using namespace romeo::controller;
using namespace romeo::model::protocols;
using namespace romeo::model::protocols::algorithms;

class TestAlgorithmsController : public QObject
{
    Q_OBJECT

public:
    explicit TestAlgorithmsController(QObject *parent = 0);

private slots:
    void getInstance();
    void checkAlgorithmName();
    void addAlgorithm();
};


#endif // TESTALGORITHMSCONTROLLER_H
