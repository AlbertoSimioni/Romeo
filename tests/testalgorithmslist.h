#ifndef TESTALGORITHMSLIST_H
#define TESTALGORITHMSLIST_H

#include <QtTest>
#define private public
#include <../src/romeo/model/protocols/algorithms/algorithmslist.h>
#include <../src/romeo/model/protocols/algorithms/userdefinedalgorithm.h>

using namespace romeo::model::protocols::algorithms;

class TestAlgorithmsList : public QObject // LCOV_EXCL_LINE
{
    Q_OBJECT

public:
    explicit TestAlgorithmsList(QObject *parent = 0);

private slots:
    void getInstance();
    void getAlgorithm();
    void addAlgorithm();
    void addAlgorithmByCopy();
};


#endif // TESTALGORITHMSLIST_H
