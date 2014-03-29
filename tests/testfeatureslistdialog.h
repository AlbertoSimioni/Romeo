#ifndef TESTFEATURESLISTDIALOG_H
#define TESTFEATURESLISTDIALOG_H

#define private public

#include <QtTest>
#include "../src/romeo/view/dialogs/featureslistdialog.h"
#include "../src/romeo/model/protocols/features/featureslist.h"
#include "../src/romeo/model/protocols/features/firstorderfeature.h"

using namespace romeo::view::dialogs;
using namespace romeo::model::protocols::features;
using namespace romeo::model;

class TestFeaturesListDialog : public QObject
{
    Q_OBJECT

public:
    explicit TestFeaturesListDialog(QObject *parent = 0);

private slots:
    void showDescription();
};

#endif // TESTFEATURESLISTDIALOG_H
