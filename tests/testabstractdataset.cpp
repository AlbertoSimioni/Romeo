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

    QString ds2dtName = "dataset2DT"; //video
    Dataset2DT *ds2dt = new Dataset2DT(ds2dtName);

    QString videoName = "video";
    QString videoPath = dataTest.absolutePath().append("/images/video.avi");
    QString videoMaskPath = dataTest.absolutePath().append("/images/videoMask.jpg");
    ds2dt->createNewSubject(videoName,videoPath,videoMaskPath);
    QList<QString> subjectVideoList;
    subjectVideoList.append(videoName); //fine video

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
    StaticProtocol *prev = sp;
    sp = new StaticProtocol(staticProtName,staticProtDescr,myAlg,clusterNum,hParameters,feat,testStaticProtocol);
    dataset2d->associateProtocol(sp);
    dataset2d->executeAnalysis(staticProtName,subjectList,dataTest.absolutePath(),true,QString(".tif"));
    delete prev;

    dataset2d->removeProtocolAssociation(staticProtName);
    myAlg = fuzzyCMeans;
    QList<QString> fParameters;
    fParameters.append(QString("epsilon"));
    fParameters.append(QString("Fuzzyness"));
    staticProtName = "staticProtName3";
    staticProtDescr = "staticProtDescription3";
    feat.append(fl->getFeature("Mean"));
    feat.append(fl->getFeature("Energy"));
    prev = sp;
    sp = new StaticProtocol(staticProtName,staticProtDescr,myAlg,clusterNum,fParameters,feat,testStaticProtocol);
    dataset2d->associateProtocol(sp);
    dataset2d->executeAnalysis(staticProtName,subjectList,dataTest.absolutePath(),true,QString(".tif"));
    delete prev;

    dataset2d->deleteSubject(firstSubjName);
    dataset2d->deleteSubject(secondSubjName);
    dataset2d->removeProtocolAssociation(staticProtName);


    features::AbstractFeature* dynMean=fl->getFeature(QString("Dynamic Mean"));

    QString dynProtName = "dynMeanDP";
    QString dynProtDescr = "dynProtDescription";
    QList<romeo::model::protocols::features::AbstractFeature*> dynFeat;
    dynFeat.append(dynMean);
    AbstractAlgorithm *notAlg;
    QList<QString> notParam;
    bool testDynamicProtocol = false;
    DynamicProtocol *dynProt = new DynamicProtocol(dynProtName,dynProtDescr,notAlg,0,notParam,dynFeat,testDynamicProtocol);
    ds2dt->associateProtocol(dynProt);

    QString pathSave= dataTest.absolutePath();
    dataTest = dataHome;
    dataTest.cd("..");
    dataTest.cd("..");
    dataTest.cd("tests");
    qDebug() << "Here I am";
    ds2dt->executeAnalysis(dynProtName,subjectVideoList,pathSave,false,QString(".png"));
    qDebug() << "Finito";
    ds2dt->removeProtocolAssociation(dynProtName);
    ds2dt->deleteSubject(videoName);

    delete sp;
    delete dynProt;
    delete ds2dt;
    delete dataset2d;
}
