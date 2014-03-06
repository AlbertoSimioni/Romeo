#include "testcontroller.h"

TestController::TestController(QObject *parent) :
    QObject(parent){
}


void TestController::getInstance(){
    QCOMPARE(Controller::getInstance(),Controller::getInstance());
}



//QTEST_MAIN(TestController)
