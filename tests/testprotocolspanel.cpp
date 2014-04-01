#include "testprotocolspanel.h"
#include "ui_protocolspanel.h"

TestProtocolsPanel::TestProtocolsPanel(QObject *parent) :
    QObject(parent){
}



void TestProtocolsPanel::fillProtocolsList(){
    ProtocolsPanel *pp = new ProtocolsPanel();

    pp->fillProtocolsList();
    QCOMPARE(pp->ui->protocolsList->topLevelItemCount(),0);

    QString datasetName = "myDataset";
    Dataset2D *ds2d = new Dataset2D(datasetName);
    pp->currentDataset = ds2d;
    pp->fillProtocolsList();
    QCOMPARE(pp->ui->newButton->isEnabled(),true);

    delete ds2d;
    delete pp;
}

void TestProtocolsPanel::changeDescription(){
    ProtocolsPanel *pp = new ProtocolsPanel();

    pp->changeDescription();
    QCOMPARE(pp->ui->descriptionText->toPlainText(),QString(""));

    QTreeWidgetItem *twi = new QTreeWidgetItem(0);
    twi->setText(0,QString("example"));
    QTreeWidgetItem *twi2 = new QTreeWidgetItem(twi);
    twi2->setText(0,QString("example2"));
    pp->ui->protocolsList->setCurrentItem(twi2);
    pp->changeDescription();
    QCOMPARE(pp->ui->descriptionText->toPlainText(),QString(""));

    delete twi;
    delete pp;
}


void TestProtocolsPanel::addProtocol(){
    ProtocolsPanel *pp = new ProtocolsPanel();

    QStringList *results = new QStringList();
    results->append(QString("myResult"));

    int previous = pp->ui->protocolsList->topLevelItemCount();

    QString algName = "algName";
    QString algDescr = "algDescription";
    QList<AbstractAlgorithm::AlgorithmParameter> paramList;
    QList<QString> algParameters;
    int clusterNum = 1;
    QString algDylp = "dylp";
    QString algDyfn = "dyfn";
    UserDefinedAlgorithm *myAlg = new UserDefinedAlgorithm(paramList,algName,algDescr,algDylp,algDyfn);


    QString staticProtName = "staticProtName";
    QString staticProtDescr = "staticProtDescription";
    QList<romeo::model::protocols::features::AbstractFeature*> feat;
    bool testStaticProtocol = false;
    int staticProtWindow = 5;
    int staticProtDistance = 2;

    romeo::model::protocols::StaticProtocol *sp = new romeo::model::protocols::StaticProtocol(staticProtName,staticProtDescr,myAlg,clusterNum,algParameters,feat,testStaticProtocol,staticProtWindow,staticProtDistance);

    QString datasetName = "myDataset";
    Dataset2D *ds2d = new Dataset2D(datasetName);
    pp->currentDataset = ds2d;

    pp->currentDataset->associateProtocol(sp);

    pp->addProtocol(staticProtName,*results);

    QCOMPARE(pp->ui->protocolsList->topLevelItemCount(),previous+1);

    delete pp;
    delete results;
    delete myAlg;
    delete sp;
    delete ds2d;
}


void TestProtocolsPanel::onDeleteClicked(){

    ProtocolsPanel *pp = new ProtocolsPanel();
    QTreeWidgetItem *twi = new QTreeWidgetItem(0);
    twi->setText(0,QString("example"));
    QTreeWidgetItem *twi2 = new QTreeWidgetItem(twi);
    twi2->setText(0,QString("example2"));
    pp->ui->protocolsList->setCurrentItem(twi2);

    pp->onDeleteClicked();

    delete twi;
    delete pp;
}

void TestProtocolsPanel::getSelectedProtocol(){
    ProtocolsPanel *pp = new ProtocolsPanel();

    QTreeWidgetItem *twi = new QTreeWidgetItem(0);
    twi->setText(0,QString("example"));
    QTreeWidgetItem *twi2 = new QTreeWidgetItem(twi);
    twi2->setText(0,QString("example2"));
    pp->ui->protocolsList->setCurrentItem(twi2);
    QCOMPARE(pp->getSelectedProtocol(),QString(""));

    delete twi;
    delete pp;
}

void TestProtocolsPanel::getCurrentDataset(){
    ProtocolsPanel *pp = new ProtocolsPanel();
    QString datasetName="DatasetProva";
    Dataset2D *dat2d=new Dataset2D(datasetName);

    pp->currentDataset = dat2d;
    QCOMPARE(pp->getCurrentDataset(),dat2d);

    delete dat2d;
    delete pp;
}

