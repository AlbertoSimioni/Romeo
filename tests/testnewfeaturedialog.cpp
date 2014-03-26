#include "testnewfeaturedialog.h"
#include "ui_newfeaturedialog.h"

TestNewFeatureDialog::TestNewFeatureDialog(QObject *parent) :
    QObject(parent)
{
}


void TestNewFeatureDialog::newFeatureDialog(){
    NewFeatureDialog *nfd = new NewFeatureDialog(0);
    QCOMPARE(nfd->ui->errorLabel->isHidden(),true);
    delete nfd;
}


void TestNewFeatureDialog::showErrorName(){
    NewFeatureDialog *nfd = new NewFeatureDialog(0);
    nfd->showErrorName(true);
    QCOMPARE(nfd->ui->errorLabel->isHidden(),false);
    nfd->showErrorName(false);
    QCOMPARE(nfd->ui->errorLabel->isHidden(),true);
    delete nfd;
}


void TestNewFeatureDialog::resetForms(){
    NewFeatureDialog *nfd = new NewFeatureDialog(0);
    nfd->resetForms();
    QCOMPARE(nfd->ui->pathLineEdit->text().isEmpty(),true);
    QCOMPARE(nfd->ui->functionLineEdit->text().isEmpty(),true);
    QCOMPARE(nfd->ui->featureLineEdit->text().isEmpty(),true);
    delete nfd;
}

void TestNewFeatureDialog::reject(){
    NewFeatureDialog *nfd = new NewFeatureDialog(0);
    nfd->reject();
    QCOMPARE(nfd->ui->pathLineEdit->text().isEmpty(),true);
    QCOMPARE(nfd->ui->functionLineEdit->text().isEmpty(),true);
    QCOMPARE(nfd->ui->featureLineEdit->text().isEmpty(),true);
    delete nfd;
}

void TestNewFeatureDialog::checkForm(){
    NewFeatureDialog *nfd = new NewFeatureDialog(0);
    nfd->checkForm();
    QCOMPARE(nfd->ui->okCancel->button(QDialogButtonBox::Ok)->isEnabled(),false);
    nfd->ui->featureLineEdit->setText(QString("sampletext"));
    nfd->ui->functionLineEdit->setText(QString("samplefunction"));
    nfd->ui->pathLineEdit->setText(QString("samplepath"));
    nfd->ui->errorLabel->setHidden(true);
    nfd->checkForm();
    QCOMPARE(nfd->ui->okCancel->button(QDialogButtonBox::Ok)->isEnabled(),true);
    delete nfd;
}
