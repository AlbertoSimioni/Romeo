#include <QString>
#include <QtTest>

#include <../src/romeo/view/dialogs/parametervalueform.h>

////////PROVA TEST
using namespace romeo::view;
using namespace romeo::view::dialogs;
using namespace romeo::model::protocols::algorithms;
using namespace romeo::model::protocols;

class TestParameterValueForm : public QObject
{
    Q_OBJECT

public:
    TestParameterValueForm();

private slots:
    void ParameterValueForm_data();
    void ParameterValueForm();
    //void CheckValidity_data();
    //void CheckValidity();
};
