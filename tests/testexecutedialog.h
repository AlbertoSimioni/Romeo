#ifndef TESTEXECUTEDIALOG_H
#define TESTEXECUTEDIALOG_H

#define private public

#include <QtTest>
#include "../src/romeo/view/dialogs/executedialog.h"
#include "../src/romeo/model/datasets/abstractdataset.h"
#include "../src/romeo/model/datasets/dataset2d.h"
#include "../src/romeo/model/datasets/dataset3d.h"

using namespace romeo::view::dialogs;
using namespace romeo::model;
using namespace romeo::model::datasets;

class TestExecuteDialog : public QObject
{
    Q_OBJECT

public:
    explicit TestExecuteDialog(QObject *parent = 0);

private slots:
    void showImage();
    void analysisFinished();
    void onNextClicked();
    void onPreviousClicked();
    void onCancelClicked();
    void addResultImage();
    void onNoFeatureClicked();
    void onFeatureExtracted();
    void onAlgorithmExecuted();
    void getCurrentDataset();
    void setCurrentDataset();
};

#endif // TESTEXECUTEDIALOG_H
