#include "testprotocoldialog.h"

TestProtocolDialog::TestProtocolDialog(QObject *parent) :
    QObject(parent){
}


void TestProtocolDialog::finishButtonClicked(){
    //qRegisterMetaType<romeo::model::protocols::ProtocolType>("romeo::model::protocols::ProtocolType");
    //romeo::model::protocols::algorithms::AlgorithmsList *al;
    //romeo::model::protocols::features::FeaturesList *fl;
    //romeo::view::dialogs::ProtocolDialog pd(al,fl); DA' FATAL ERROR
    //QSignalSpy spy(&pd, SIGNAL(createProtocol(QString,QString,bool,QList<QString>,QString,romeo::model::protocols::ProtocolType,int,int))); //controlla i segnali emessi
    //pd.finishButtonClicked();
    //QCOMPARE(spy.count(),1);
    //QVERIFY2(spy.takeFirst().at(0).type() == QVariant::Bool, "Il segnale emesso da CheckValidity() non ha un bool come parametro"); //controlla che il segnale emesso abbia un bool come parametro
    }



//QTEST_MAIN(TestProtocolDialog)

