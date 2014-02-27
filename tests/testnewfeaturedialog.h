#ifndef TESTNEWFEATUREDIALOG_H
#define TESTNEWFEATUREDIALOG_H

#define private public

#include "../src/romeo/view/dialogs/newdatasetdialog.h"
#include <QtTest>
#include <QDialogButtonBox>

class TestNewFeatureDialog : public QObject
{
    Q_OBJECT
public:
    explicit TestNewFeatureDialog(QObject *parent = 0);

public slots:
    void NewDatasetDialog_data();
    void NewDatasetDialog();
};

#endif // TESTNEWFEATUREDIALOG_H
