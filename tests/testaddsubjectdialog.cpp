#include "testaddsubjectdialog.h"
#include "ui_addsubjectdialog.h"
#include <QPushButton>

TestAddSubjectDialog::TestAddSubjectDialog(QObject *parent) :
    QObject(parent)
{
}


void TestAddSubjectDialog::OkButtonClicked(){
    AddSubjectDialog *ndd = new AddSubjectDialog(0);
    QSignalSpy spy(ndd, SIGNAL(createNewSubject(QString,QString,QString)));

    ndd->okButtonClicked();
    QCOMPARE(spy.count(),1);

    QList<QVariant> arguments = spy.takeFirst(); // take the first signal

    QString qs;
    QVariant qv(qs);

    QVERIFY2(arguments.at(0).type() == qv.type(), "Il segnale emesso da OKButtonClicked() non ha un QString come primo parametro");
    delete ndd;
}

void TestAddSubjectDialog::showErrorName(){
    AddSubjectDialog *ndd = new AddSubjectDialog(0);
    ndd->showErrorName(true);
    QCOMPARE(ndd->ui->errorLabel->isHidden(),false);
    ndd->showErrorName(false);
    QCOMPARE(ndd->ui->errorLabel->isHidden(),true);
    delete ndd;
}

void TestAddSubjectDialog::resetForms(){
    AddSubjectDialog *ndd = new AddSubjectDialog(0);
    ndd->resetForms();
    QCOMPARE(ndd->ui->nameLineEdit->text().isEmpty(),true);
    delete ndd;
}

void TestAddSubjectDialog::reject(){
    AddSubjectDialog *ndd = new AddSubjectDialog(0);
    ndd->reject();
    QCOMPARE(ndd->ui->nameLineEdit->text().isEmpty(),true);
    delete ndd;
}

void TestAddSubjectDialog::checkForm(){
    AddSubjectDialog *ndd = new AddSubjectDialog(0);
    ndd->checkForm();
    QCOMPARE(ndd->ui->okCancel->button(QDialogButtonBox::Ok)->isEnabled(),false);
    ndd->ui->nameLineEdit->setText(QString("sampletext"));
    ndd->ui->pathDataLineEdit->setText(QString("samplepath"));
    ndd->ui->errorLabel->setHidden(true);
    ndd->checkForm();
    QCOMPARE(ndd->ui->okCancel->button(QDialogButtonBox::Ok)->isEnabled(),true);
    delete ndd;
}
