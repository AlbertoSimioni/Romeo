#ifndef TESTADDSUBJECTDIALOG_H
#define TESTADDSUBJECTDIALOG_H

#define private public

#include <QtTest>
#include "../src/romeo/view/dialogs/addsubjectdialog.h"

using namespace romeo::view::dialogs;
using namespace romeo::model;

class TestAddSubjectDialog : public QObject
{
    Q_OBJECT

public:
    explicit TestAddSubjectDialog(QObject *parent = 0);

private slots:
    void OkButtonClicked();
    void showErrorName();
    void resetForms();
    void reject();
    void checkForm();
    void changeFilters();
};

#endif // TESTADDSUBJECTDIALOG_H
