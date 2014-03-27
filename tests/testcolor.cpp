#include "testcolor.h"

TestColor::TestColor(QObject *parent) :
    QObject(parent){
}


void TestColor::getColor_data(){
    QTest::addColumn<int>("index");
    QTest::addColumn<int>("first");
    QTest::addColumn<int>("second");
    QTest::addColumn<int>("third");

    QTest::newRow("red")<< 0 << 238 << 0 << 0;
    QTest::newRow("blue")<< 1 << 0 << 0 << 128;
    QTest::newRow("green")<< 2 << 0 << 205 << 0;
    QTest::newRow("yellow")<< 3 << 255 << 255 << 0;
    QTest::newRow("magenta")<< 4 << 255 << 0 << 255;
    QTest::newRow("lightblue")<< 5 << 135 << 206 << 250;
    QTest::newRow("gray")<< 6 << 115 << 115 << 115;
    QTest::newRow("orange")<< 7 << 238 << 118 << 0;
    QTest::newRow("aquagreen")<< 8 << 0 << 255 << 255;
    QTest::newRow("pink")<< 9 << 255 << 130 << 171;
    QTest::newRow("extracolor")<< 10 << 255 << 255 << 255;
}


void TestColor::getColor(){
    Color *c = new Color();
    QFETCH(int,index);
    QFETCH(int,first);
    QFETCH(int,second);
    QFETCH(int,third);
    int color[3] = {first,second,third};

    if(index<=9 && index >=0){
        QCOMPARE(c->getColor(index)[0],color[0]);
        QCOMPARE(c->getColor(index)[1],color[1]);
        QCOMPARE(c->getColor(index)[2],color[2]);
    }
    else{
        QVERIFY(c->getColor(index)[0] < 256);
        QVERIFY(c->getColor(index)[1] < 256);
        QVERIFY(c->getColor(index)[2] < 256);
    }
    delete c;
}
