#include "testnewalgorithmparameterform.h"
#include "ui_newalgorithmparameterform.h"

TestNewAlgorithmParameterForm::TestNewAlgorithmParameterForm(QObject *parent) :
    QObject(parent){
}


void TestNewAlgorithmParameterForm::newAlgorithmParameterForm_data(){
    /*QTest::addColumn<AbstractAlgorithm::ParameterType>("type");

    QTest::newRow("Char") << AbstractAlgorithm::CHAR;
    QTest::newRow("Bool") << AbstractAlgorithm::BOOL;
    QTest::newRow("Double") << AbstractAlgorithm::DOUBLE;
    QTest::newRow("Int") << AbstractAlgorithm::INT;*/
}

void TestNewAlgorithmParameterForm::newAlgorithmParameterForm(){
    NewAlgorithmParameterForm *napf = new NewAlgorithmParameterForm();

    QCOMPARE(napf->ui->defaultLineEdit->isHidden(),false);

    delete napf;
}




void TestNewAlgorithmParameterForm::checkValidity_data()
{
    QTest::addColumn<QString>("textEntry");
    QTest::addColumn<AbstractAlgorithm::ParameterType>("returnType");

    QTest::newRow("Char") << "Char" << AbstractAlgorithm::CHAR;
    QTest::newRow("Bool") << "Boolean" << AbstractAlgorithm::BOOL;
    QTest::newRow("Double") << "Double" << AbstractAlgorithm::DOUBLE;
    QTest::newRow("Int") << "Integer" << AbstractAlgorithm::INT;
}

void TestNewAlgorithmParameterForm::checkValidity()
{
    QFETCH(QString, textEntry);
    QFETCH(AbstractAlgorithm::ParameterType, returnType);

    NewAlgorithmParameterForm *napf = new NewAlgorithmParameterForm();

    napf->ui->typeCombo->setCurrentText(textEntry);

    QSignalSpy spy(napf,SIGNAL(valueEntered()));

    napf->checkValidity();

    QCOMPARE(spy.count(),1);

    delete napf;
}

void TestNewAlgorithmParameterForm::getType_data(){
    QTest::addColumn<QString>("textEntry");
    QTest::addColumn<AbstractAlgorithm::ParameterType>("returnType");

    QTest::newRow("Char") << "Char" << AbstractAlgorithm::CHAR;
    QTest::newRow("Bool") << "Boolean" << AbstractAlgorithm::BOOL;
    QTest::newRow("Double") << "Double" << AbstractAlgorithm::DOUBLE;
    QTest::newRow("Int") << "Integer" << AbstractAlgorithm::INT;
}

void TestNewAlgorithmParameterForm::getType(){
    QFETCH(QString, textEntry);
    QFETCH(AbstractAlgorithm::ParameterType, returnType);

    NewAlgorithmParameterForm *napf = new NewAlgorithmParameterForm();

    napf->ui->typeCombo->setCurrentText(textEntry);

    QCOMPARE(napf->getType(),returnType);

    delete napf;
}

void TestNewAlgorithmParameterForm::getName(){
     NewAlgorithmParameterForm *napf = new NewAlgorithmParameterForm();

     QString name = "name";

     napf->ui->valueLineEdit->setText(name);

     QCOMPARE(napf->getName(),name);

     delete napf;
}

void TestNewAlgorithmParameterForm::getDefault(){
     NewAlgorithmParameterForm *napf = new NewAlgorithmParameterForm();

     QString defaultValue = "default";

     napf->ui->defaultLineEdit->setText(defaultValue);

     QCOMPARE(napf->getDefault(),defaultValue);

     delete napf;
}

void TestNewAlgorithmParameterForm::isValid(){
     NewAlgorithmParameterForm *napf = new NewAlgorithmParameterForm();

     bool valid = true;

     napf->valid = valid;

     QCOMPARE(napf->isValid(),valid);

     valid = false;

     napf->valid = valid;

     QCOMPARE(napf->isValid(),valid);

     delete napf;
}

void TestNewAlgorithmParameterForm::onDeleteCliked(){
     NewAlgorithmParameterForm *napf = new NewAlgorithmParameterForm();

     QSignalSpy spy(napf,SIGNAL(deletePressed(NewAlgorithmParameterForm*)));

     napf->onDeleteClicked();

     QCOMPARE(spy.count(),1);

     delete napf;
}
