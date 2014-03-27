#ifndef TESTCOLOR_H
#define TESTCOLOR_H

#include <QtTest>
#include <../src/romeo/model/protocols/color.h>

using namespace romeo::model::protocols;

class TestColor : public QObject{
    Q_OBJECT

public:
    explicit TestColor(QObject *parent = 0);

private slots:
   void getColor_data();
   void getColor();
};


#endif // TESTCOLOR_H
