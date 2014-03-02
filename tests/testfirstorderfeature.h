#ifndef TESTFIRSTORDERFEATURE_H
#define TESTFIRSTORDERFEATURE_H

#include <QtTest>
//#define private public
#include <../src/romeo/model/protocols/features/firstorderfeature.h>

using namespace romeo::model::protocols::features;

class TestFirstOrderFeature : public QObject // LCOV_EXCL_LINE
{
    Q_OBJECT

public:
    explicit TestFirstOrderFeature(QObject *parent = 0);

private slots:
    void firstorderFeature();
};


#endif // TESTFIRSTORDERFEATURE_H
