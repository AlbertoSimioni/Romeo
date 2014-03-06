#ifndef TESTNEWDATASETDIALOG_H
#define TESTNEWDATASETDIALOG_H

#define private public

#include <QtTest>
#include "../src/romeo/view/dialogs/newdatasetdialog.h"

using namespace romeo::view::dialogs;
using namespace romeo::model;

class TestNewDatasetDialog : public QObject
{
    Q_OBJECT

public:
    explicit TestNewDatasetDialog(QObject *parent = 0);

private slots:
    void OkButtonClicked();
    void showErrorName();
    void resetForms();
    void reject();
    void checkForm();
};

#endif // TESTNEWDATASETDIALOG_H
