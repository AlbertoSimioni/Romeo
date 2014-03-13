#include "testprotocoldialog.h"
#include "ui_protocoldialog.h"

TestProtocolDialog::TestProtocolDialog(QObject *parent) :
    QObject(parent){
}


void TestProtocolDialog::protocolDialog(){
    QString algName = "algName";
    QString algDescr = "description";
    QList<AbstractAlgorithm::AlgorithmParameter> paramList;
    QString algDylp = "dylp";
    QString algDyfn = "dyfn";

    QString featName = "feat1Name";
    QString featDescr = "description";
    QString featDylp = "dylp";
    QString featDyfn = "dyfn";

    QString feat2Name = "feat2Name";
    QString feat3Name = "feat3Name";

    AlgorithmsList *al = new AlgorithmsList();
    al->addAlgorithm(algName,algDescr,paramList,algDylp,algDyfn);
    FeaturesList *fl = new FeaturesList();
    fl->addFeature(featName,DYNAMIC,featDescr,featDylp,featDyfn);
    fl->addFeature(feat2Name,FIRSTORDER,featDescr,featDylp,featDyfn);
    fl->addFeature(feat3Name,SECONDORDER,featDescr,featDylp,featDyfn);


    ProtocolDialog *pd = new ProtocolDialog(al,fl,0);
    QCOMPARE(pd->ui->AlgorithmCombo->currentText(), algName);
    QVERIFY(pd->featuresList->getFeature(featName)!=false);
    QVERIFY(pd->featuresList->getFeature(feat2Name)!=false);
    QVERIFY(pd->featuresList->getFeature(feat3Name)!=false);

    delete al;
    delete fl;
    delete pd;
}


void TestProtocolDialog::showErrorName(){
    AlgorithmsList *al = new AlgorithmsList();
    FeaturesList *fl = new FeaturesList();
    ProtocolDialog *pd = new ProtocolDialog(al,fl,0);
    pd->showErrorName(true);
    QCOMPARE(pd->ui->errorLabel->isHidden(),false);
    pd->showErrorName(false);
    QCOMPARE(pd->ui->errorLabel->isHidden(),true);
    delete al;
    delete fl;
    delete pd;
}


void TestProtocolDialog::resetForms(){
    AlgorithmsList *al = new AlgorithmsList();
    FeaturesList *fl = new FeaturesList();
    ProtocolDialog *pd = new ProtocolDialog(al,fl,0);
    pd->resetForms();
    QCOMPARE(pd->ui->protocolLineEdit->text().isEmpty(),true);
    delete al;
    delete fl;
    delete pd;
}

void TestProtocolDialog::reject(){
    AlgorithmsList *al = new AlgorithmsList();
    FeaturesList *fl = new FeaturesList();
    ProtocolDialog *pd = new ProtocolDialog(al,fl,0);
    pd->reject();
    QCOMPARE(pd->ui->protocolLineEdit->text().isEmpty(),true);
    delete al;
    delete fl;
    delete pd;
}

void TestProtocolDialog::finishButtonClicked(){
    QString algName = "algName";
    QString algDescr = "description";
    QList<AbstractAlgorithm::AlgorithmParameter> paramList;
    QString algDylp = "dylp";
    QString algDyfn = "dyfn";

    QString featName = "feat1Name";
    QString featDescr = "description";
    QString featDylp = "dylp";
    QString featDyfn = "dyfn";

    QString feat2Name = "feat2Name";
    QString feat3Name = "feat3Name";

    AlgorithmsList *al = new AlgorithmsList();
    al->addAlgorithm(algName,algDescr,paramList,algDylp,algDyfn);
    FeaturesList *fl = new FeaturesList();
    fl->addFeature(featName,DYNAMIC,featDescr,featDylp,featDyfn);
    fl->addFeature(feat2Name,FIRSTORDER,featDescr,featDylp,featDyfn);
    fl->addFeature(feat3Name,SECONDORDER,featDescr,featDylp,featDyfn);

    ProtocolDialog *pd = new ProtocolDialog(al,fl,0);

    qRegisterMetaType<romeo::model::protocols::ProtocolType>("romeo::model::protocols::ProtocolType");
    QSignalSpy spy(pd,SIGNAL(createProtocol(QString,QString,bool,QList<QString>,QString,romeo::model::protocols::ProtocolType,int,int,int,QList<QString>)));

    pd->ui->dataTypeCombo->setEditText(QString("Static"));
    pd->finishButtonClicked();

    pd->ui->dataTypeCombo->setEditText(QString("Dynamic"));
    pd->finishButtonClicked();

    QCOMPARE(spy.count(),2);
    delete al;
    delete fl;
    delete pd;
}

void TestProtocolDialog::nextStep(){
    AlgorithmsList *al = new AlgorithmsList();
    FeaturesList *fl = new FeaturesList();
    ProtocolDialog *pd = new ProtocolDialog(al,fl,0);

    pd->nextStep();
    QCOMPARE(pd->ui->Wizard->currentIndex(),1);
    pd->ui->Wizard->setCurrentIndex(1);
    pd->nextStep();
    QCOMPARE(pd->ui->Wizard->currentIndex(),2);

    delete al;
    delete fl;
    delete pd;
}

void TestProtocolDialog::previousStep(){
    AlgorithmsList *al = new AlgorithmsList();
    FeaturesList *fl = new FeaturesList();
    ProtocolDialog *pd = new ProtocolDialog(al,fl,0);

    pd->ui->Wizard->setCurrentIndex(0);
    pd->previousStep();
    QCOMPARE(pd->ui->Wizard->currentIndex(),0);
    pd->ui->Wizard->setCurrentIndex(2);
    pd->previousStep();
    QCOMPARE(pd->ui->Wizard->currentIndex(),1);

    delete al;
    delete fl;
    delete pd;
}

void TestProtocolDialog::addFeature(){
    /*AlgorithmsList *al = new AlgorithmsList();
    FeaturesList *fl = new FeaturesList();
    ProtocolDialog *pd = new ProtocolDialog(al,fl,0);
    pd->
    delete al;
    delete fl;
    delete pd;*/
}

void TestProtocolDialog::addButtonClicked(){
    AlgorithmsList *al = new AlgorithmsList();
    FeaturesList *fl = new FeaturesList();
    ProtocolDialog *pd = new ProtocolDialog(al,fl,0);

    pd->addButtonClicked();
    QCOMPARE(pd->ui->featuresList->selectedItems().isEmpty(),true);

    delete al;
    delete fl;
    delete pd;
}

void TestProtocolDialog::removeButtonClicked(){
    AlgorithmsList *al = new AlgorithmsList();
    FeaturesList *fl = new FeaturesList();
    ProtocolDialog *pd = new ProtocolDialog(al,fl,0);

    pd->removeButtonClicked();
    QCOMPARE(pd->ui->featuresList->selectedItems().isEmpty(),true);

    delete al;
    delete fl;
    delete pd;
}

void TestProtocolDialog::fillFeaturesList(){
    AlgorithmsList *al = new AlgorithmsList();
    FeaturesList *fl = new FeaturesList();
    ProtocolDialog *pd = new ProtocolDialog(al,fl,0);
    pd->fillFeaturesList();
    QCOMPARE(pd->ui->protocolFeaturesList->count(),0);
    delete al;
    delete fl;
    delete pd;
}

void TestProtocolDialog::changeParametersForm(){
    AlgorithmsList *al = new AlgorithmsList();
    FeaturesList *fl = new FeaturesList();
    ProtocolDialog *pd = new ProtocolDialog(al,fl,0);

    pd->changeParametersForm();
    AbstractAlgorithm* algorithm = pd->algorithmsList->getAlgorithm(pd->ui->AlgorithmCombo->currentText());
    QVERIFY(!algorithm);

    delete al;
    delete fl;
    delete pd;
}

void TestProtocolDialog::checkEmpty(){
    AlgorithmsList *al = new AlgorithmsList();
    FeaturesList *fl = new FeaturesList();
    ProtocolDialog *pd = new ProtocolDialog(al,fl,0);

    pd->checkEmpty(QString(""));
    QCOMPARE(pd->ui->next1->isEnabled(),false);
    pd->ui->next1->setEnabled(true);
    pd->checkEmpty(QString("notEmpty"));
    QCOMPARE(pd->ui->next1->isEnabled(),true);

    delete al;
    delete fl;
    delete pd;
}

void TestProtocolDialog::checkWindowsSizeGLCM(){
    AlgorithmsList *al = new AlgorithmsList();
    FeaturesList *fl = new FeaturesList();
    ProtocolDialog *pd = new ProtocolDialog(al,fl,0);
    bool b = true;

    pd->checkWindowSizeGLCM();

    QCOMPARE(pd->ui->next2->isEnabled(),true);

    delete al;
    delete fl;
    delete pd;
}
