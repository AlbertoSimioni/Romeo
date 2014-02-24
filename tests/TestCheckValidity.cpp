#include "TestCheckValidity.h"

TestCheckValidity::TestCheckValidity()
{
}

void TestCheckValidity::CheckValidity_data()
{
    QTest::addColumn<QString>("inputvalue");
    QTest::addColumn<QString>("type");
    QTest::addColumn<QString>("expectedValidity");

    QTest::newRow("ValidChar") << "h" << "AbstractAlgorithm::CHAR" << "TRUE";
    QTest::newRow("InvalidChar") << "h" << "AbstractAlgorithm::BOOL" << "FALSE";
    QTest::newRow("InvalidChar") << "h" << "AbstractAlgorithm::DOUBLE" << "FALSE";
    QTest::newRow("InvalidChar") << "h" << "AbstractAlgorithm::INT" << "FALSE";

    QTest::newRow("") << "TRUE" << "AbstractAlgorithm::CHAR" << "FALSE";
    QTest::newRow("") << "TRUE" << "AbstractAlgorithm::BOOL" << "TRUE";
    QTest::newRow("") << "TRUE" << "AbstractAlgorithm::DOUBLE" << "FALSE";
    QTest::newRow("") << "TRUE" << "AbstractAlgorithm::INT" << "FALSE";

    QTest::newRow("") << "25.95" << "AbstractAlgorithm::CHAR" << "FALSE";
    QTest::newRow("") << "25.95" << "AbstractAlgorithm::BOOL" << "FALSE";
    QTest::newRow("") << "25.95" << "AbstractAlgorithm::DOUBLE" << "TRUE";
    QTest::newRow("") << "25.95" << "AbstractAlgorithm::INT" << "FALSE";

    QTest::newRow("") << "25" << "AbstractAlgorithm::CHAR" << "FALSE";
    QTest::newRow("") << "25" << "AbstractAlgorithm::BOOL" << "FALSE";
    QTest::newRow("") << "25" << "AbstractAlgorithm::DOUBLE" << "FALSE";
    QTest::newRow("") << "25" << "AbstractAlgorithm::INT" << "TRUE";
}

void TestCheckValidity::CheckValidity()
{
    QFETCH(QString, inputvalue);
    QFETCH(QString, type);

    AbstractAlgorithm::AlgorithmParameter param (QString("param"),AbstractAlgorithm::CHAR, QString("default"));

    ParameterValueForm pvf(param,0);
    pvf.CheckValidity(QString());

    QCOMPARE((pvf.isValid(),expectedValidity);
}


QTEST_MAIN(TestCheckValidity)

