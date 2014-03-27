#ifndef TESTEXECUTEPANEL_H
#define TESTEXECUTEPANEL_H

#include <QtTest>
#define private public
#include <../src/romeo/view/mainWindow/executepanel.h>

#include <../src/romeo/model/datasets/dataset2d.h>
#include <../src/romeo/model/datasets/dataset2dt.h>
#include <../src/romeo/model/datasets/dataset3d.h>
#include <../src/romeo/model/datasets/dataset3dt.h>


using namespace romeo::view::mainWindow;
using namespace romeo::model::datasets;

class TestExecutePanel : public QObject
{
    Q_OBJECT

public:
    explicit TestExecutePanel(QObject *parent = 0);

private slots:
    void setCurrentDataset();
    void onStartClicked();
    void onViewResultsClicked();
};


#endif // TESTEXECUTEPANEL_H
