#include "testnewdatasetdialog.h"
#include "ui_newdatasetdialog.h"
#include <QPushButton>

TestNewDatasetDialog::TestNewDatasetDialog(QObject *parent) :
    QObject(parent)
{
}


void TestNewDatasetDialog::OkButtonClicked(){
    qRegisterMetaType<romeo::model::InputFormat>("romeo::model::InputFormat");
    NewDatasetDialog *ndd = new NewDatasetDialog(0);
    QSignalSpy spy(ndd, SIGNAL(createDataset(QString,romeo::model::InputFormat)));

    ndd->okButtonClicked();
    QCOMPARE(spy.count(),1);

    QList<QVariant> arguments = spy.takeFirst(); // take the first signal

    QString qs;
    QVariant qv(qs);

    QVERIFY2(arguments.at(0).type() == qv.type(), "Il segnale emesso da OKButtonClicked() non ha un QString come primo parametro");


    //InputFormat type;
    //QVariant qv2(type);

    /*QVERIFY2(arguments.at(1).type() == qv2.type()
             || arguments.at(1).type() == QVariant(TYPE2D).type()
             || arguments.at(1).type() == QVariant(TYPE2DT).type()
             || arguments.at(1).type() == QVariant(TYPE3D).type()
             || arguments.at(1).type() == QVariant(TYPE3DT).type(), "Il segnale emesso da OKButtonClicked() non ha un romeo::model::InputFormat come secondo parametro");
*/


    //spy.takeFirst().at(0).type();
    //QVERIFY(spy.takeFirst().at(0).type() == QString);
    //QVERIFY(spy.takeFirst().at(0).type() == romeo::model::InputFormat);
    //QCOMPARE(ui,a.ui);
}

void TestNewDatasetDialog::showErrorName(){
    NewDatasetDialog *ndd = new NewDatasetDialog(0);
    ndd->showErrorName(true);
    QCOMPARE(ndd->ui->ErrorLabel->isHidden(),false);
    ndd->showErrorName(false);
    QCOMPARE(ndd->ui->ErrorLabel->isHidden(),true);
}

void TestNewDatasetDialog::resetForms(){
    NewDatasetDialog *ndd = new NewDatasetDialog(0);
    ndd->resetForms();
    QCOMPARE(ndd->ui->nameLineEdit->text().isEmpty(),true);
}

void TestNewDatasetDialog::reject(){
    NewDatasetDialog *ndd = new NewDatasetDialog(0);
    ndd->reject();
    QCOMPARE(ndd->ui->nameLineEdit->text().isEmpty(),true);
}

void TestNewDatasetDialog::checkForm(){
    NewDatasetDialog *ndd = new NewDatasetDialog(0);
    ndd->checkForm();
    QCOMPARE(ndd->ui->okCancel->button(QDialogButtonBox::Ok)->isEnabled(),false);
    ndd->ui->nameLineEdit->setText(QString("sampletext"));
    ndd->ui->ErrorLabel->setHidden(true);
    ndd->checkForm();
    QCOMPARE(ndd->ui->okCancel->button(QDialogButtonBox::Ok)->isEnabled(),true);
}


//QTEST_MAIN(TestNewDatasetDialog)
