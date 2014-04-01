#ifndef TESTNEWALGORITHMDIALOG_H
#define TESTNEWALGORITHMDIALOG_H



#include <QtTest>
#define private public
#include "../src/romeo/view/dialogs/newalgorithmdialog.h"
#include "../src/romeo/model/protocols/algorithms/abstractalgorithm.h"

using namespace romeo::view::dialogs;

class TestNewAlgorithmDialog : public QObject
{
    Q_OBJECT

public:
    explicit TestNewAlgorithmDialog(QObject *parent = 0);

private slots:
    void newAlgorithmDialog();
    void showErrorName();
    void resetForms();
    void reject();
    void checkForm();
    void addButtonClicked();
};

#endif // TESTNEWALGORITHMDIALOG_H
