#include "TestParameterValueForm.h"



void TestParameterValueForm::ParameterValueForm_data(){
    QTest::addColumn<AbstractAlgorithm::ParameterType>("type");

    QTest::newRow("") << AbstractAlgorithm::CHAR;
    QTest::newRow("") << AbstractAlgorithm::BOOL;
    QTest::newRow("") << AbstractAlgorithm::DOUBLE;
    QTest::newRow("") << AbstractAlgorithm::INT;
}

void TestParameterValueForm::ParameterValueForm(){
    QFETCH(AbstractAlgorithm::ParameterType, type);
    bool expectedValidity = false;

    AbstractAlgorithm::AlgorithmParameter param(QString("param"), type, QString("default"));

    romeo::view::dialogs::ParameterValueForm pvf(param);

    QString expectedName=param.getName();

    QCOMPARE(expectedName,pvf.getName());

    QCOMPARE(pvf.isValid(),expectedValidity);

    AbstractAlgorithm::ParameterType expectedType = param.getType();

    QCOMPARE(expectedType,pvf.getType());

    QCOMPARE(QTest::toString(param),QTest::toString(pvf.getParameter()));

    QString expectedValue=param.getDefaultParameter();

    QCOMPARE(expectedValue,pvf.getValue());
    }



/*
void TestParameterValueForm::CheckValidity_data()
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
}*/

/*void TestParameterValueForm::CheckValidity()
{
    QFETCH(QString, inputvalue);
    QFETCH(QString, type);
    QFETCH(QString, expectedValidity);

    AbstractAlgorithm::AlgorithmParameter param (QString("param"),AbstractAlgorithm::CHAR, QString("default"));

    ParameterValueForm pvf(param,0);
    pvf.checkValidity(QString());

    QCOMPARE(pvf.isValid(),expectedValidity);
}
*/

QTEST_MAIN(TestParameterValueForm)

