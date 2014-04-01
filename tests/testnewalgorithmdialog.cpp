#include "testnewalgorithmdialog.h"
#include "ui_newalgorithmdialog.h"

TestNewAlgorithmDialog::TestNewAlgorithmDialog(QObject *parent) :
    QObject(parent)
{
}


void TestNewAlgorithmDialog::newAlgorithmDialog(){
    NewAlgorithmDialog *nad = new NewAlgorithmDialog(0);
    QCOMPARE(nad->ui->errorLabel->isHidden(),true);
    delete nad;
}


void TestNewAlgorithmDialog::showErrorName(){
    NewAlgorithmDialog *nad = new NewAlgorithmDialog(0);
    nad->showErrorName(true);
    QCOMPARE(nad->ui->errorLabel->isHidden(),false);
    nad->showErrorName(false);
    QCOMPARE(nad->ui->errorLabel->isHidden(),true);
    delete nad;
}


void TestNewAlgorithmDialog::resetForms(){
    NewAlgorithmDialog *nad = new NewAlgorithmDialog(0);
    nad->resetForms();
    QCOMPARE(nad->ui->pathLineEdit->text().isEmpty(),true);
    QCOMPARE(nad->ui->functionName->text().isEmpty(),true);
    QCOMPARE(nad->ui->algorithmLineEdit->text().isEmpty(),true);
    delete nad;
}

void TestNewAlgorithmDialog::reject(){
    NewAlgorithmDialog *nad = new NewAlgorithmDialog(0);
    nad->reject();
    QCOMPARE(nad->ui->pathLineEdit->text().isEmpty(),true);
    QCOMPARE(nad->ui->functionName->text().isEmpty(),true);
    QCOMPARE(nad->ui->algorithmLineEdit->text().isEmpty(),true);
    delete nad;
}


void TestNewAlgorithmDialog::checkForm(){
    NewAlgorithmDialog *nad = new NewAlgorithmDialog(0);
    nad->checkForm();
    QCOMPARE(nad->ui->okCancel->button(QDialogButtonBox::Ok)->isEnabled(),false);
    nad->ui->algorithmLineEdit->setText(QString("sampletext"));
    nad->ui->functionName->setText(QString("sampletext"));
    nad->ui->pathLineEdit->setText(QString("sampletext"));
    nad->ui->errorLabel->setHidden(true);
    nad->checkForm();
    QCOMPARE(nad->ui->okCancel->button(QDialogButtonBox::Ok)->isEnabled(),true);
    delete nad;
}

void TestNewAlgorithmDialog::addButtonClicked(){
    NewAlgorithmDialog *nad = new NewAlgorithmDialog(0);
    nad->addButtonClicked();
}
