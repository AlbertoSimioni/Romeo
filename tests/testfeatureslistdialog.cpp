#include "testfeatureslistdialog.h"
#include "ui_featureslistdialog.h"

TestFeaturesListDialog::TestFeaturesListDialog(QObject *parent) :
    QObject(parent)
{
}


void TestFeaturesListDialog::showDescription(){
    FeaturesList *fl = new FeaturesList();

    QString name = "featName";
    QString descr = "description";
    QString dylp = "dylp";
    QString dyfn = "dyfn";

    FirstOrderFeature *df = new FirstOrderFeature(name,dylp,dyfn,descr);

    fl->addFeature(df);

    FeaturesListDialog *fld = new FeaturesListDialog(fl);

    QTreeWidgetItem *itm =new QTreeWidgetItem(fld->ui->featureTable);
    itm->setText(0,fl->getFeaturesList()[0]->getName());

    fld->ui->featureTable->addTopLevelItem(itm);

    fld->ui->featureTable->selectAll();

    fld->showDescription();

    QCOMPARE(fld->ui->descriptionText->toPlainText(), QString("Type: First Order \n"));

    delete fl;
}
