#ifndef TESTPARAMETERVALUEFORM_H
#define TESTPARAMETERVALUEFORM_H

#include <QtTest>
#define private public
#include <../src/romeo/view/dialogs/parametervalueform.h>

using namespace romeo::model::protocols::algorithms;

#ifndef PARAM_H
#define PARAM_H
Q_DECLARE_METATYPE(AbstractAlgorithm::ParameterType);
#endif

class TestParameterValueForm : public QObject 
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
