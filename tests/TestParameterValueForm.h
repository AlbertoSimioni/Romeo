#include <QString>
#include <QtTest>

#include <../src/romeo/view/dialogs/parametervalueform.h>

////////PROVA TEST
using namespace romeo::view;
using namespace romeo::view::dialogs;
using namespace romeo::model::protocols::algorithms;
using namespace romeo::model::protocols;

Q_DECLARE_METATYPE(AbstractAlgorithm::ParameterType);

class TestParameterValueForm : public QObject // LCOV_EXCL_LINE
{
    Q_OBJECT

public:

private slots:
    void ParameterValueForm_data();
    void ParameterValueForm();
    //void CheckValidity_data();
    //void CheckValidity();
};
