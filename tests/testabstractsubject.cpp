#include "testabstractsubject.h"

TestAbstractSubject::TestAbstractSubject(QObject *parent) :
    QObject(parent){
}
void TestAbstractSubject::getNameSubjectMask(){
    QString name="nome";
    QString imPath="imPath";
    QString maskPath="maskPAth";
    Subject2D *s2d=new Subject2D(name,imPath,maskPath);
    QString testName=s2d->getName();
    QString testSub=s2d->getSubject();
    QString testMask=s2d->getMask();

    QCOMPARE(testName,name);
    QCOMPARE(testSub,imPath);
    QCOMPARE(testMask,maskPath);
    delete s2d;
}

//QTEST_MAIN(TestAbstractSubject)

