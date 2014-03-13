#ifndef TESTSUBJECT2DT_H
#define TESTSUBJECT2DT_H

#include <QtTest>
#include <../src/romeo/model/datasets/subject2dt.h>

using namespace romeo::model::datasets;

#ifndef INPUTFORMAT
#define INPUTFORMAT
Q_DECLARE_METATYPE(romeo::model::InputFormat);
#endif

class TestSubject2DT : public QObject{
    Q_OBJECT

public:
    explicit TestSubject2DT(QObject *parent = 0);

private slots:
   void getType();
   void getType_data();
};


#endif // TESTSUBJECT2DT_H
