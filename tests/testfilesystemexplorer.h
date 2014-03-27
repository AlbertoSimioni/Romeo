#ifndef TESTFILESYSTEMEXPLORER_H
#define TESTFILESYSTEMEXPLORER_H

#define private public

#include <QtTest>
#include "../src/romeo/view/mainWindow/filesystemexplorer.h"

using namespace romeo::view::mainWindow;
using namespace romeo::model;

class TestFileSystemExplorer : public QObject
{
    Q_OBJECT

public:
    explicit TestFileSystemExplorer(QObject *parent = 0);

private slots:
    void setCurrentInputFormat();
    void changeFilters();
};

#endif // TESTFILESYSTEMEXPLORER_H
