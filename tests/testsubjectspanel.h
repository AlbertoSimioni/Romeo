#ifndef TESTSUBJECTSPANEL_H
#define TESTSUBJECTSPANEL_H

#include <QtTest>
#define private public
#include <../src/romeo/view/mainWindow/subjectspanel.h>

#include <../src/romeo/model/datasets/dataset2d.h>
#include <../src/romeo/model/datasets/dataset2dt.h>
#include <../src/romeo/model/datasets/dataset3d.h>
#include <../src/romeo/model/datasets/dataset3dt.h>


using namespace romeo::view::mainWindow;
using namespace romeo::model::datasets;

class TestSubjectsPanel : public QObject
{
    Q_OBJECT

public:
    explicit TestSubjectsPanel(QObject *parent = 0);

private slots:
    void setCurrentDataset();
    void getCurrentDataset();
    void fillSubjectsList();
    void onDeleteClicked();
    void getCheckedSubjects();
};


#endif // TESTSUBJECTSPANEL_H
