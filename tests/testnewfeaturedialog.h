#ifndef TESTNEWFEATUREDIALOG_H
#define TESTNEWFEATUREDIALOG_H

#define private public

#include <QtTest>
#include "../src/romeo/view/dialogs/newfeaturedialog.h"
#include "../src/romeo/model/protocols/features/abstractfeature.h"


class TestNewFeatureDialog : public QObject
{
    Q_OBJECT

public:
    explicit TestNewFeatureDialog(QObject *parent = 0);

private slots:
    void OkButtonClicked();
};

#endif // TESTNEWFEATUREDIALOG_H
