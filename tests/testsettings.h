#ifndef TESTSETTINGS_H
#define TESTSETTINGS_H

#include <QtTest>
#define private public
#include <../src/romeo/model/settings.h>

using namespace romeo::model;

class TestSettings : public QObject
{
    Q_OBJECT

public:
    explicit TestSettings(QObject *parent = 0);

private slots:
    void getInstance();
};


#endif // TESTSETTINGS_H
