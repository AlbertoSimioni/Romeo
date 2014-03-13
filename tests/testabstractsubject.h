#ifndef TESTABSTRACTSUBJECT_H
#define TESTABSTRACTSUBJECT_H

#include <QtTest>
#include <../src/romeo/model/datasets/subject2d.h>

using namespace romeo::model::datasets;

class TestAbstractSubject : public QObject
{
    Q_OBJECT

public:
    explicit TestAbstractSubject(QObject *parent = 0);

private slots:
    void getNameSubjectMask();
};


#endif // TESTABSTRACTSUBJECT_H
