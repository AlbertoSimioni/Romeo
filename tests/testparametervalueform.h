#ifndef TESTPARAMETERVALUEFORM_H
#define TESTPARAMETERVALUEFORM_H

#include <QtTest>
#define private public
#include <../src/romeo/view/dialogs/parametervalueform.h>

using namespace romeo::view;
using namespace romeo::view::dialogs;
using namespace romeo::model::protocols::algorithms;
using namespace romeo::model::protocols;

Q_DECLARE_METATYPE(AbstractAlgorithm::ParameterType);

class TestParameterValueForm : public QObject // LCOV_EXCL_LINE
{
    Q_OBJECT

public:
    explicit TestParameterValueForm(QObject *parent = 0);

private slots:
    void ParameterValueForm_data();
    void ParameterValueForm();
    void CheckValidity_data();
    void CheckValidity();
};


#endif // TESTPARAMETERVALUEFORM_H
