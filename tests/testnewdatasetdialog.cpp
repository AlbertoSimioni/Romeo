#include "testnewdatasetdialog.h"

TestNewDatasetDialog::TestNewDatasetDialog(QObject *parent) :
    QObject(parent)
{
}


void TestNewDatasetDialog::OkButtonClicked(){
    //Ui::NewDatasetDialog *ui(Ui::NewDatasetDialog);
    //ui->setupUi(this);
    //ui->ErrorLabel->setHidden(true);
    //ui->okCancel->button(QDialogButtonBox::Ok)->setEnabled(false);
    qRegisterMetaType<romeo::model::InputFormat>("romeo::model::InputFormat");
    romeo::view::dialogs::NewDatasetDialog ndd(0);
    QSignalSpy spy(&ndd, SIGNAL(createDataset(QString,romeo::model::InputFormat)));
    ndd.okButtonClicked();
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


//QTEST_MAIN(TestNewDatasetDialog)
