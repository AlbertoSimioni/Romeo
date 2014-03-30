#ifndef TESTNEWALGORITHMPARAMETERFORM_H
#define TESTNEWALGORITHMPARAMETERFORM_H

#include <QtTest>
#define private public
#include <../src/romeo/view/dialogs/newalgorithmparameterform.h>

using namespace romeo::model::protocols::algorithms;
using namespace romeo::view::dialogs;

#ifndef PARAM_H
#define PARAM_H
Q_DECLARE_METATYPE(AbstractAlgorithm::ParameterType);
#endif

class TestNewAlgorithmParameterForm : public QObject 
{
    Q_OBJECT

public:
    explicit TestNewAlgorithmParameterForm(QObject *parent = 0);

private slots:
    void newAlgorithmParameterForm();
    void checkValidity_data();
    void checkValidity();
    void getType_data();
    void getType();
    void getName();
    void getDefault();
    void isValid();
    void onDeleteCliked();
};


#endif // TESTNEWALGORITHMPARAMETERFORM_H
