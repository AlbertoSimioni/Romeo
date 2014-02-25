#include "TestParameterValueForm.h"


TestParameterValueForm::TestParameterValueForm()
{
}

void TestParameterValueForm::ParameterValueForm_data(){

    QTest::addColumn<QString>("type");
    QTest::addColumn<bool>("expectedValidity");

    QTest::newRow("") << "AbstractAlgorithm::CHAR" << false;
    QTest::newRow("") << "AbstractAlgorithm::BOOL" << false;
    QTest::newRow("") << "AbstractAlgorithm::DOUBLE" << false;
    QTest::newRow("") << "AbstractAlgorithm::INT" << false;
}

void TestParameterValueForm::ParameterValueForm(){
    QFETCH(QString, type);
    QFETCH(bool, expectedValidity);

    AbstractAlgorithm::AlgorithmParameter param(QString("param"), AbstractAlgorithm::CHAR, QString("default"));

    if(type=="AbstractAlgorithm::BOOL")
            AbstractAlgorithm::AlgorithmParameter param(QString("param"), AbstractAlgorithm::BOOL, QString("default"));
    if(type=="AbstractAlgorithm::DOUBLE")
            AbstractAlgorithm::AlgorithmParameter param(QString("param"), AbstractAlgorithm::DOUBLE, QString("default"));
    if(type=="AbstractAlgorithm::INT")
            AbstractAlgorithm::AlgorithmParameter param(QString("param"), AbstractAlgorithm::INT, QString("default"));

    romeo::view::dialogs::ParameterValueForm pvf(param);

    QCOMPARE(QString(pvf.isValid()),QString(expectedValidity));


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

