#ifndef TESTSUBJECT3DT_H
#define TESTSUBJECT3DT_H

#include <QtTest>
#include <../src/romeo/model/datasets/subject3dt.h>

using namespace romeo::model::datasets;

#ifndef INPUTFORMAT
#define INPUTFORMAT
Q_DECLARE_METATYPE(romeo::model::InputFormat);
#endif

class TestSubject3DT : public QObject{
    Q_OBJECT

public:
    explicit TestSubject3DT(QObject *parent = 0);

private slots:
   void getType();
   void getType_data();
};


#endif // TESTSUBJECT3DT_H
