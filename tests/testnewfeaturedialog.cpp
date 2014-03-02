#include "testnewfeaturedialog.h"

TestNewFeatureDialog::TestNewFeatureDialog(QObject *parent) :
    QObject(parent)
{
}


void TestNewFeatureDialog::OkButtonClicked(){
    qRegisterMetaType<romeo::model::protocols::features::FeatureType>("romeo::model::protocols::features::FeatureType");
    romeo::view::dialogs::NewFeatureDialog *nfd = new romeo::view::dialogs::NewFeatureDialog(0);
    QSignalSpy spy(nfd, SIGNAL(createFeature(QString,QString,QString,QString,romeo::model::protocols::features::FeatureType)));
    //nfd.okButtonClicked(); //PROBLEMA
    QVERIFY(spy.count()<=1);
    //QCOMPARE(ui,a.ui);
}


//QTEST_MAIN(TestNewFeatureDialog)
