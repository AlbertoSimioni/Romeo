#include "testsettings.h"

TestSettings::TestSettings(QObject *parent) :
    QObject(parent){
}



void TestSettings::getInstance()
{
    Settings s(0);
    QCOMPARE(s.getInstance(0), s.getInstance(0)); //verifico che per entrambe le chiamate l'istanza restituita sia sempre la stessa
}

//QTEST_MAIN(TestSettings)

