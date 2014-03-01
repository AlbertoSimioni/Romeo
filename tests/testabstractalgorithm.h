#ifndef TESTABSTRACTALGORITHM_H
#define TESTABSTRACTALGORITHM_H

#include <QtTest>
//#define private public
#include <../src/romeo/model/protocols/algorithms/abstractalgorithm.h>

using namespace romeo::model::protocols::algorithms;
#ifndef PARAM_H
#define PARAM_H
Q_DECLARE_METATYPE(AbstractAlgorithm::ParameterType);
#endif

class TestAbstractAlgorithm : public QObject // LCOV_EXCL_LINE
{
    Q_OBJECT

public:
    explicit TestAbstractAlgorithm(QObject *parent = 0);

private slots:
    void algorithmParameter_data();
    void algorithmParameter();
    void getTypeString_data();
    void getTypeString();
};


#endif // TESTABSTRACTALGORITHM_H
