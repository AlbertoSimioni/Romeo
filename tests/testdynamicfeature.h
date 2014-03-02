#ifndef TESTDYNAMICFEATURE_H
#define TESTDYNAMICFEATURE_H

#include <QtTest>
//#define private public
#include <../src/romeo/model/protocols/features/dynamicfeature.h>

using namespace romeo::model::protocols::features;

class TestDynamicFeature : public QObject // LCOV_EXCL_LINE
{
    Q_OBJECT

public:
    explicit TestDynamicFeature(QObject *parent = 0);

private slots:
    void dynamicFeature();
};


#endif // TESTDYNAMICFEATURE_H
