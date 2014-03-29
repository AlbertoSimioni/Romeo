#ifndef TESTFEATURESCONTROLLER_H
#define TESTFEATURESCONTROLLER_H

#include <QtTest>
#define private public
#include <../src/romeo/controller/controller.h>
#include <../src/romeo/controller/featurescontroller.h>
#include <../src/romeo/model/protocols/features/featureslist.h>
#include <../src/romeo/model/protocols/features/firstorderfeature.h>
#include <../src/romeo/model/protocols/features/secondorderfeature.h>
#include <../src/romeo/model/protocols/features/dynamicfeature.h>

using namespace romeo::controller;
using namespace romeo::model::protocols;

class TestFeaturesController : public QObject
{
    Q_OBJECT

public:
    explicit TestFeaturesController(QObject *parent = 0);

private slots:
    void getInstance();
    void checkFeatureName();
    void addFeature();
};


#endif // TESTFEATURESCONTROLLER_H
