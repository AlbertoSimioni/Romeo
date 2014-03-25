#include "testcontroller.h"
#include "ui_protocoldialog.h"
#include "ui_newalgorithmdialog.h"
#include "ui_newfeaturedialog.h"
#include "ui_newdatasetdialog.h"
#include "ui_addsubjectdialog.h"

TestController::TestController(QObject *parent) :
    QObject(parent){
}


void TestController::getInstance(){
    QCOMPARE(Controller::getInstance(),Controller::getInstance());
}


void TestController::checkProtocolName(){
    Controller *controller = Controller::getInstance();

    controller->checkProtocolName(QString("notExists"));
    QCOMPARE(controller->protocolDialog->ui->errorLabel->isHidden(),true);

    QString algName = "algName";
    QString algDescr = "algDescription";
    QList<algorithms::AbstractAlgorithm::AlgorithmParameter> paramList;
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

    ProtocolsList *protList = ProtocolsList::getInstance();

    protList->addProtocol(staticProtName,staticProtDescr,myAlg,clusterNum,algParameters,feat,testStaticProtocol,STATIC,staticProtWindow,staticProtDistance);


    controller->checkProtocolName(staticProtName);
    QCOMPARE(controller->protocolDialog->ui->next1->isEnabled(),false);

    protList->removeProtocol(staticProtName);
    delete myAlg;
}

void TestController::checkAlgorithmName(){
    Controller *controller = Controller::getInstance();

    controller->checkAlgorithmName(QString("notExists"));
    QCOMPARE(controller->newAlgorithmDialog->ui->errorLabel->isHidden(),true);

    QString algName = "algName2";
    QString algDescr = "algDescription";
    QList<algorithms::AbstractAlgorithm::AlgorithmParameter> paramList;
    QList<QString> algParameters;
    int clusterNum = 1;
    QString algDylp = "dylp";
    QString algDyfn = "dyfn";
    UserDefinedAlgorithm *myAlg = new UserDefinedAlgorithm(paramList,algName,algDescr,algDylp,algDyfn);

    AlgorithmsList *algList = AlgorithmsList::getInstance();

    algList->addAlgorithm(myAlg);

    controller->checkAlgorithmName(algName);
    QCOMPARE(controller->newAlgorithmDialog->ui->okCancel->button(QDialogButtonBox::Ok)->isEnabled(),false);

    delete myAlg;
}

void TestController::checkFeatureName(){
    Controller *controller = Controller::getInstance();

    controller->checkFeatureName(QString("notExists"));
    QCOMPARE(controller->newFeatureDialog->ui->errorLabel->isHidden(),true);

    features::FeaturesList *list = features::FeaturesList::getInstance();

    QString featName = "featName";
    features::FirstOrderFeature *foFeat = new features::FirstOrderFeature(featName,QString("fodylp"),QString("fodyfn"),QString("fodescription"));

    list->addFeature(foFeat);

    controller->checkFeatureName(featName);
    QCOMPARE(controller->newFeatureDialog->ui->okCancel->button(QDialogButtonBox::Ok)->isEnabled(),false);

    delete foFeat;
}

void TestController::checkDatasetName(){

    Controller *controller = Controller::getInstance();

    controller->checkDatasetName(QString("notExists"));
    QCOMPARE(controller->newDatasetDialog->ui->ErrorLabel->isHidden(),true);

    DatasetsList *list = DatasetsList::getInstance();

    QString datasetName = "dataset2D";
    list->addDataset(datasetName,romeo::model::TYPE2D);

    controller->checkDatasetName(datasetName);
    QCOMPARE(controller->newDatasetDialog->ui->okCancel->button(QDialogButtonBox::Ok)->isEnabled(),false);

    //list->deleteDataset(list->getDataset(datasetName));
}

void TestController::checkSubjectName(){

    Controller *controller = Controller::getInstance();

    DatasetsList *list = DatasetsList::getInstance();

    QString datasetName = "mydataset2D";
    list->addDataset(datasetName,romeo::model::TYPE2D);

    Dataset2D *ds2d= dynamic_cast<Dataset2D*>(list->getDataset(datasetName));
    QString subjName = "subjName";
    QString subjFileSubject = "fileSubject";
    QString subjMask = "subjMask";

    controller->mainWindow->getDatasetPanel()->setCurrentDataset(ds2d);

    controller->mainWindow->getDatasetPanel()->getCurrentDataset()->createNewSubject(subjName,subjFileSubject,subjMask);

    controller->checkSubjectName(subjName);

    QCOMPARE(controller->addSubjectDialog->ui->okCancel->button(QDialogButtonBox::Ok)->isEnabled(),false);

    controller->mainWindow->getDatasetPanel()->getCurrentDataset()->deleteSubject(subjName);

    controller->checkSubjectName(subjName);

    QCOMPARE(controller->addSubjectDialog->ui->okCancel->button(QDialogButtonBox::Ok)->isEnabled(),true);
}

void TestController::addProtocol(){

    Controller *controller = Controller::getInstance();

    controller->checkProtocolName(QString("notExists"));
    QCOMPARE(controller->protocolDialog->ui->errorLabel->isHidden(),true);

    QString algName = "algName3";
    QString algDescr = "algDescription";
    QList<algorithms::AbstractAlgorithm::AlgorithmParameter> paramList;
    QList<QString> algParameters;
    int clusterNum = 1;
    QString algDylp = "dylp";
    QString algDyfn = "dyfn";
    UserDefinedAlgorithm *myAlg = new UserDefinedAlgorithm(paramList,algName,algDescr,algDylp,algDyfn);

    AlgorithmsList *algList = AlgorithmsList::getInstance();

    algList->addAlgorithm(myAlg);


    QString staticProtName = "staticProtName";
    QString staticProtDescr = "staticProtDescription";
    QList<romeo::model::protocols::features::AbstractFeature*> feat;
    QList<QString> features;
    bool testStaticProtocol = false;
    int staticProtWindow = 5;
    int staticProtDistance = 2;


    controller->addProtocol(staticProtName,staticProtDescr,testStaticProtocol,features,algName,STATIC,staticProtWindow,staticProtDistance,clusterNum,algParameters);


    ProtocolsList *protList = ProtocolsList::getInstance();

    QVERIFY(protList->getProtocol(staticProtName) != false);

}


void TestController::addAlgorithm(){

    Controller *controller = Controller::getInstance();

    QString algName = "algName4";
    QString algDescr = "algDescription";
    QList<algorithms::AbstractAlgorithm::AlgorithmParameter> paramList;
    QList<QString> algParameters;
    int clusterNum = 1;
    QString algDylp = "dylp";
    QString algDyfn = "dyfn";

    AlgorithmsList *algList = AlgorithmsList::getInstance();

    controller->addAlgorithm(algName,algDescr,algDyfn,algDylp,paramList);

    QCOMPARE(algList->getAlgorithm(algName)->getName(),algName);

}

void TestController::addFeature(){

    Controller *controller = Controller::getInstance();

    features::FeaturesList *list = features::FeaturesList::getInstance();

    QString featName = "featName3";

    controller->addFeature(featName,QString("fodescription"),QString("fodyfn"),QString("fodylp"),features::FIRSTORDER);

    QCOMPARE(list->getFeature(featName)->getName(),featName);
}

void TestController::addDataset(){

    Controller *controller = Controller::getInstance();

    DatasetsList *list = DatasetsList::getInstance();

    QString datasetName = "myDataset2D";
    controller->addDataset(datasetName,romeo::model::TYPE2D);

    QCOMPARE(list->getDataset(datasetName)->getName(),datasetName);

    //list->deleteDataset(list->getDataset(datasetName));
}

void TestController::addSubject(){

    Controller *controller = Controller::getInstance();

    DatasetsList *list = DatasetsList::getInstance();

    QString datasetName = "newDataset";
    list->addDataset(datasetName,romeo::model::TYPE2D);

    Dataset2D *ds2d = dynamic_cast<Dataset2D*>(list->getDataset(datasetName));
    QString subjName = "subjName";
    QString subjFileSubject = "fileSubject";
    QString subjMask = "subjMask";

    controller->mainWindow->getDatasetPanel()->setCurrentDataset(ds2d);

    controller->addSubject(subjName,subjFileSubject,subjMask);

    QCOMPARE(list->getDataset(datasetName)->getSubject(subjName)->getName(),subjName);
    //list->deleteDataset(list->getDataset(datasetName));
}

void TestController::deleteSubject(){

    Controller *controller = Controller::getInstance();

    DatasetsList *list = DatasetsList::getInstance();

    QString datasetName = "newDataset2";
    list->addDataset(datasetName,romeo::model::TYPE2D);

    Dataset2D *ds2d = dynamic_cast<Dataset2D*>(list->getDataset(datasetName));
    QString subjName = "subjName2";
    QString subjFileSubject = "fileSubject";
    QString subjMask = "subjMask";

    controller->mainWindow->getDatasetPanel()->setCurrentDataset(ds2d);

    controller->mainWindow->getDatasetPanel()->getCurrentDataset()->createNewSubject(subjName,subjFileSubject,subjMask);

    QCOMPARE(list->getDataset(datasetName)->subjects.isEmpty(),false);

    controller->deleteSubject(subjName);

    QCOMPARE(list->getDataset(datasetName)->subjects.isEmpty(),true);
    //list->deleteDataset(list->getDataset(datasetName));

}

void TestController::deleteProtocol(){

    Controller *controller = Controller::getInstance();

}

void TestController::deleteCurrentDataset(){

    Controller *controller = Controller::getInstance();

}

void TestController::associateProtocol(){

    Controller *controller = Controller::getInstance();

}

void TestController::removeProtocolAssociation(){

    Controller *controller = Controller::getInstance();

}


/*void TestController::viewNewProtocolDialog(){
    Controller *controller = Controller::getInstance();

    controller->viewNewProtocolDialog();

    QCOMPARE(controller->protocolDialog->result(),1);
}
*/
