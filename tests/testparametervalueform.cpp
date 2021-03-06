#include "testparametervalueform.h"

TestParameterValueForm::TestParameterValueForm(QObject *parent) :
    QObject(parent){
}


void TestParameterValueForm::ParameterValueForm_data(){
    QTest::addColumn<AbstractAlgorithm::ParameterType>("type");

    QTest::newRow("Char") << AbstractAlgorithm::CHAR;
    QTest::newRow("Bool") << AbstractAlgorithm::BOOL;
    QTest::newRow("Double") << AbstractAlgorithm::DOUBLE;
    QTest::newRow("Int") << AbstractAlgorithm::INT;
}

void TestParameterValueForm::ParameterValueForm(){
    QFETCH(AbstractAlgorithm::ParameterType, type);
    bool expectedValidity = false;

    AbstractAlgorithm::AlgorithmParameter param(QString("param"), type, QString("default"));

    romeo::view::dialogs::ParameterValueForm *pvf = new romeo::view::dialogs::ParameterValueForm(param);

    QString expectedName = param.getName();

    QCOMPARE(expectedName,pvf->getName());

    QCOMPARE(pvf->isValid(),expectedValidity);

    AbstractAlgorithm::ParameterType expectedType = param.getType();

    QCOMPARE(expectedType,pvf->getType());

    QCOMPARE(QTest::toString(param),QTest::toString(pvf->getParameter()));

    QString expectedValue=param.getDefaultParameter();

    QCOMPARE(expectedValue,pvf->getValue());
    delete pvf;
}




void TestParameterValueForm::CheckValidity_data()
{
    QTest::addColumn<QString>("inputvalue");
    QTest::addColumn<AbstractAlgorithm::ParameterType>("type");
    QTest::addColumn<bool>("expectedValidity");

    QTest::newRow("ValidChar") << "h" << AbstractAlgorithm::CHAR << true;
    QTest::newRow("InvalidChar") << "h" << AbstractAlgorithm::BOOL << false;
    QTest::newRow("InvalidChar") << "h" << AbstractAlgorithm::DOUBLE << false;
    QTest::newRow("InvalidChar") << "h" << AbstractAlgorithm::INT << false;

    QTest::newRow("InvalidBool") << "true" << AbstractAlgorithm::CHAR << false;
    QTest::newRow("InvalidBool") << "true" << AbstractAlgorithm::DOUBLE << false;
    QTest::newRow("InvalidBool") << "true" << AbstractAlgorithm::INT << false;

    QTest::newRow("InvalidDouble") << "25.95" << AbstractAlgorithm::CHAR << false;
    QTest::newRow("InvalidDouble") << "25.95" << AbstractAlgorithm::BOOL << false;
    QTest::newRow("ValidDouble") << "25.95" << AbstractAlgorithm::DOUBLE << true;
    QTest::newRow("InvalidDouble") << "25.95" << AbstractAlgorithm::INT << false;

    QTest::newRow("InvalidInt") << "25" << AbstractAlgorithm::CHAR << false;
    QTest::newRow("InvalidInt") << "25" << AbstractAlgorithm::BOOL << false;
    QTest::newRow("ValidInt") << "25" << AbstractAlgorithm::INT << true;
}

void TestParameterValueForm::CheckValidity()
{
    QFETCH(QString, inputvalue);
    QFETCH(AbstractAlgorithm::ParameterType, type);
    QFETCH(bool, expectedValidity);

    AbstractAlgorithm::AlgorithmParameter param (QString("param"),type, QString("default"));

    romeo::view::dialogs::ParameterValueForm *pvf = new romeo::view::dialogs::ParameterValueForm(param);
    QSignalSpy spy(pvf, SIGNAL(valueEntered(bool))); //controlla i segnali emessi
    pvf->checkValidity(inputvalue);
    QVERIFY2(spy.takeFirst().at(0).type() == QVariant::Bool, "Il segnale emesso da CheckValidity() non ha un bool come parametro"); //controlla che il segnale emesso abbia un bool come parametro
    QCOMPARE(pvf->isValid(),expectedValidity);
    delete pvf;
}
