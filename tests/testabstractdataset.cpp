#include "testabstractdataset.h"
#include <QDebug>

TestAbstractDataset::TestAbstractDataset(QObject *parent) :
    QObject(parent){
}

void TestAbstractDataset::createNewSubject(){
    QDir dataTest = QDir::current();
    dataTest.cd("..");
    dataTest.cd("..");
    dataTest.cd("tests");

    QString name="NomeDataset";
    QString fileSubject=dataTest.absolutePath().append("/images/image.tif");
    QString mask=dataTest.absolutePath().append("/images/mask.tif");
    Dataset2D *ds2d=new Dataset2D(name);
    QSignalSpy spyAddSub(ds2d, SIGNAL(addedSubject(QString,QString,QString)));
    QSignalSpy spyMod(ds2d, SIGNAL(modified(QString)));
    ds2d->createNewSubject(name,fileSubject,mask);
    //controlla i segnali emessi
    QCOMPARE(spyAddSub.count(),1);
    QCOMPARE(spyMod.count(),1);
    delete ds2d;
}

void TestAbstractDataset::getName(){
    QString name="name";
    Dataset2D *ds2d=new Dataset2D(name);
    QCOMPARE(ds2d->getName(),name);
    delete ds2d;
}

void TestAbstractDataset::setName(){
    QString name="name";
    Dataset2D *ds2d=new Dataset2D(name);
    QString nameChanged="nameChanged";
    ds2d->setName(nameChanged);
    QCOMPARE(ds2d->getName(),nameChanged);
    delete ds2d;
}

void TestAbstractDataset::getProtocolResults(){
    QString name="name";
    Dataset2D *ds2d=new Dataset2D(name);
    QString protocol="protocol";
    QStringList strList= ds2d->getProtocolResults(protocol);
    QStringList null;
    QList<Result *> strListRes= ds2d->getResultsList(protocol);
    QList<Result *> nullList;
    QCOMPARE(strList,null);
    QCOMPARE(strListRes,nullList);
    delete ds2d;
}

void TestAbstractDataset::executeAnalysis(){
    DatasetsController* controller = DatasetsController::getInstance();
    features::FeaturesList *fl = features::FeaturesList::getInstance();

    QDir dataHome = QDir::current();
    QDir dataTest = QDir::current();
    dataTest.cd("..");
    dataTest.cd("..");
    dataTest.cd("tests");

    QString name = "myDataset";
    Dataset2D *dataset2d = new Dataset2D(name);
    QSignalSpy spyAnalysisFinished(dataset2d,SIGNAL(analysisFinished()));
    QSignalSpy spyNewResults(dataset2d,SIGNAL(newResults()));
    AbstractAlgorithm *myAlg;

    QList<AbstractAlgorithm::AlgorithmParameter> param;
    AbstractAlgorithm::AlgorithmParameter param1 (QString("Distance"), AbstractAlgorithm::CHAR, QString("e"));
    AbstractAlgorithm::AlgorithmParameter param2 (QString("Maximum number of iterations"), AbstractAlgorithm::INT, QString("200"));
    param.append(param1);
    param.append(param2);
    AbstractAlgorithm* kMeans = KMeans::getInstance(param, QString("K-means"), QString("desc"));

    QList<AbstractAlgorithm::AlgorithmParameter> paramh;
    AbstractAlgorithm::AlgorithmParameter paramh1 (QString("Distance"), AbstractAlgorithm::CHAR, QString("e"));
    AbstractAlgorithm::AlgorithmParameter paramh2 (QString("Linkage criteria"), AbstractAlgorithm::CHAR, QString("s"));
    paramh.append(paramh1);
    paramh.append(paramh2);
    AbstractAlgorithm* hierarchical = Hierarchical::getInstance(paramh, QString("Hierarchical"), QString("desc"));


    QList<AbstractAlgorithm::AlgorithmParameter> paramf;
    AbstractAlgorithm::AlgorithmParameter paramf1 (QString("epsilon"), AbstractAlgorithm::DOUBLE, QString("0.0001"));
    AbstractAlgorithm::AlgorithmParameter paramf2 (QString("Fuzzyness"), AbstractAlgorithm::INT, QString("2"));
    paramf.append(paramf1);
    paramf.append(paramf2);
    AbstractAlgorithm *fuzzyCMeans = FuzzyCMeans::getInstance(paramf, QString("Fuzzy C-Means"), QString("desc"));

    myAlg = kMeans;
    QList<QString> algParameters;
    algParameters.append(QString("Distance"));
    algParameters.append(QString("Maximum number of iterations"));
    int clusterNum = 3;

    QString staticProtName = "staticProtName";
    QString staticProtDescr = "staticProtDescription";
    QList<romeo::model::protocols::features::AbstractFeature*> feat;
    bool testStaticProtocol = false;
    StaticProtocol *sp = new StaticProtocol(staticProtName,staticProtDescr,myAlg,clusterNum,algParameters,feat,testStaticProtocol);
    dataset2d->associateProtocol(sp);

    QString firstSubjName = "subjectNoMask";
    QString secondSubjName = "subjectWithMask";
    QString imgPath = dataTest.absolutePath().append("/images/image.tif");
    QString maskPath = "";
    dataset2d->createNewSubject(firstSubjName,imgPath,maskPath);
    maskPath = dataTest.absolutePath().append("/images/mask.tif");
    dataset2d->createNewSubject(secondSubjName,imgPath,maskPath);
    QList<QString> subjectList;
    subjectList.append(firstSubjName);
    subjectList.append(secondSubjName);

    dataTest = dataHome;
    if(!dataTest.cd("dataTest"))
    {
        dataTest.mkdir("dataTest");
        dataTest.cd("dataTest");
    }

    dataset2d->executeAnalysis(staticProtName,subjectList,dataTest.absolutePath(),true,QString(".tif"));

    dataset2d->removeProtocolAssociation(staticProtName);
    myAlg = hierarchical;
    QList<QString> hParameters;
    hParameters.append(QString("Distance"));
    hParameters.append(QString("Linkage criteria"));
    staticProtName = "staticProtName2";
    staticProtDescr = "staticProtDescription2";
    sp = new StaticProtocol(staticProtName,staticProtDescr,myAlg,clusterNum,hParameters,feat,testStaticProtocol);
    dataset2d->associateProtocol(sp);
    dataset2d->executeAnalysis(staticProtName,subjectList,dataTest.absolutePath(),true,QString(".tif"));

    dataset2d->removeProtocolAssociation(staticProtName);
    myAlg = fuzzyCMeans;
    QList<QString> fParameters;
    fParameters.append(QString("epsilon"));
    fParameters.append(QString("Fuzzyness"));
    staticProtName = "staticProtName3";
    staticProtDescr = "staticProtDescription3";
    feat.append(fl->getFeature("Mean"));
    feat.append(fl->getFeature("Energy"));
    sp = new StaticProtocol(staticProtName,staticProtDescr,myAlg,clusterNum,fParameters,feat,testStaticProtocol);
    dataset2d->associateProtocol(sp);
    dataset2d->executeAnalysis(staticProtName,subjectList,dataTest.absolutePath(),true,QString(".tif"));

    QCOMPARE(spyAnalysisFinished.count(),3);
    QCOMPARE(spyNewResults.count(),3);

    dataset2d->deleteSubject(firstSubjName);
    dataset2d->deleteSubject(secondSubjName);
    dataset2d->removeProtocolAssociation(staticProtName);
}
