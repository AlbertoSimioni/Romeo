#include "testabstractsubject.h"

TestAbstractSubject::TestAbstractSubject(QObject *parent) :
    QObject(parent){
}
void TestAbstractSubject::getNameSubjectMask(){
    QDir dataTest = QDir::current();
    dataTest.cd("..");
    dataTest.cd("..");
    dataTest.cd("tests");

    QString name = "nome";
    QString imPath = dataTest.absolutePath().append("/images/image.tif");
    QString maskPath = dataTest.absolutePath().append("/images/mask.tif");
    Subject2D *s2d = new Subject2D(name,imPath,maskPath);
    QString testName = s2d->getName();
    QString testSub = s2d->getSubject();
    QString testMask = s2d->getMask();

    QCOMPARE(testName,name);
    QCOMPARE(testSub,imPath);
    QCOMPARE(testMask,maskPath);
    delete s2d;
}

