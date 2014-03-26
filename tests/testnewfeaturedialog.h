#ifndef TESTNEWFEATUREDIALOG_H
#define TESTNEWFEATUREDIALOG_H



#include <QtTest>
#define private public
#include "../src/romeo/view/dialogs/newfeaturedialog.h"
#include "../src/romeo/model/protocols/features/abstractfeature.h"

using namespace romeo::view::dialogs;

class TestNewFeatureDialog : public QObject
{
    Q_OBJECT

public:
    explicit TestNewFeatureDialog(QObject *parent = 0);

private slots:
    void newFeatureDialog();
    void showErrorName();
    void resetForms();
    void reject();
    void checkForm();
};

#endif // TESTNEWFEATUREDIALOG_H
