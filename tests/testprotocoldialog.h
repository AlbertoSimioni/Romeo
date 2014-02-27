#ifndef TESTPROTOCOLDIALOG_H
#define TESTPROTOCOLDIALOG_H

#include <QtTest>
#define private public
#include <../src/romeo/view/dialogs/protocoldialog.h>

using namespace romeo::model::protocols;


class TestProtocolDialog : public QObject // LCOV_EXCL_LINE
{
    Q_OBJECT

public:
    explicit TestProtocolDialog(QObject *parent = 0);

private slots:
    void finishButtonClicked();
};


#endif // TESTPROTOCOLDIALOG_H
