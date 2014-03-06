#ifndef TESTSUBJECT2D_H
#define TESTSUBJECT2D_H

#include <QtTest>
//#define private public
#include <../src/romeo/model/datasets/subject2d.h>

using namespace romeo::model::datasets;

#ifndef INPUTFORMAT_H
#define INPUTFORMAT_H
Q_DECLARE_METATYPE(romeo::model::InputFormat);
#endif

class TestSubject2D : public QObject{
    Q_OBJECT

public:
    explicit TestSubject2D(QObject *parent = 0);

private slots:
   void getType();
   void getType_data();
};


#endif // TESTSUBJECT2D_H
