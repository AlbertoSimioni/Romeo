#ifndef TESTSECONDORDERFEATURE_H
#define TESTSECONDORDERFEATURE_H

#include <QtTest>
//#define private public
#include <../src/romeo/model/protocols/features/secondorderfeature.h>

using namespace romeo::model::protocols::features;

class TestSecondOrderFeature : public QObject // _LINE
{
    Q_OBJECT

public:
    explicit TestSecondOrderFeature(QObject *parent = 0);

private slots:
    void secondOrderFeature();
};


#endif // TESTSECONDORDERFEATURE_H
