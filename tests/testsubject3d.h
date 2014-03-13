#ifndef TESTSUBJECT3D_H
#define TESTSUBJECT3D_H

#include <QtTest>
#include <../src/romeo/model/datasets/subject3d.h>

using namespace romeo::model::datasets;

#ifndef INPUTFORMAT
#define INPUTFORMAT
Q_DECLARE_METATYPE(romeo::model::InputFormat);
#endif

class TestSubject3D : public QObject{
    Q_OBJECT

public:
    explicit TestSubject3D(QObject *parent = 0);

private slots:
   void getType();
   void getType_data();
};


#endif // TESTSUBJECT3D_H
