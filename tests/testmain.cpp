#include <QApplication>
#include <QtTest>
#include "testnewfeaturedialog.h"
#include "testparametervalueform.h"

int main(int argc, char*argv[]){ //main relativo all'esecuzione dei test
    QApplication a(argc, argv);

    TestParameterValueForm tvf;
    QTest::qExec(&tvf);

    TestNewFeatureDialog tfd;
    QTest::qExec(&tfd);

    return 0;
}
