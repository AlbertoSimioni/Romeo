#include "testabstractalgorithm.h"

TestAbstractAlgorithm::TestAbstractAlgorithm(QObject *parent) :
    QObject(parent){
}

void TestAbstractAlgorithm::algorithmParameter_data()
{
    QTest::addColumn<AbstractAlgorithm::ParameterType>("type");

    QTest::newRow("Char") << AbstractAlgorithm::CHAR;
    QTest::newRow("Bool") << AbstractAlgorithm::BOOL;
    QTest::newRow("Double") << AbstractAlgorithm::DOUBLE;
    QTest::newRow("Int") << AbstractAlgorithm::INT;
}

void TestAbstractAlgorithm::algorithmParameter(){
    QString name = "name";
    QFETCH(AbstractAlgorithm::ParameterType, type);
    QString defaultPar = "default";

    AbstractAlgorithm::AlgorithmParameter param(name,type,defaultPar);
    QCOMPARE(name,param.getName());
    QCOMPARE(type,param.getType());
    QCOMPARE(defaultPar,param.getDefaultParameter());
}




void TestAbstractAlgorithm::getTypeString_data()
{
    QTest::addColumn<AbstractAlgorithm::ParameterType>("type");
    QTest::addColumn<QString>("expectedTypeString");

    QTest::newRow("Char") << AbstractAlgorithm::CHAR << "CHAR";
    QTest::newRow("Bool") << AbstractAlgorithm::BOOL << "BOOL";
    QTest::newRow("Double") << AbstractAlgorithm::DOUBLE << "DOUBLE";
    QTest::newRow("Int") << AbstractAlgorithm::INT << "INT";
}

void TestAbstractAlgorithm::getTypeString()
{
    QString name = "name";
    QFETCH(AbstractAlgorithm::ParameterType, type);
    QString defaultPar = "default";

    AbstractAlgorithm::AlgorithmParameter param(name,type,defaultPar);

    QFETCH(QString, expectedTypeString);

    QCOMPARE(expectedTypeString,param.getTypeString());

}


//QTEST_MAIN(TestAbstractAlgorithm)

