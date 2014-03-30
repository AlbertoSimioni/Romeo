#include "testdynamicprotocol.h"

TestDynamicProtocol::TestDynamicProtocol(QObject *parent) :
    QObject(parent){
}


DynamicProtocol* TestDynamicProtocol::createProtocol(){
    QString algName = "algName";
    QString algDescr = "algDescription";
    QList<algorithms::AbstractAlgorithm::AlgorithmParameter> paramList;
    QList<QString> algParameters;
    int clusterNum = 1;
    QString algDylp = "dylp";
    QString algDyfn = "dyfn";
    algorithms::UserDefinedAlgorithm *myAlg = new algorithms::UserDefinedAlgorithm(paramList,algName,algDescr,algDylp,algDyfn);

    QString protName = "protName";
    QString protDescr = "protDescription";
    QList<romeo::model::protocols::features::AbstractFeature*> feat;
    bool testProtocol = false;

    return new DynamicProtocol(protName,protDescr,myAlg,clusterNum,algParameters,feat,testProtocol);
}


void TestDynamicProtocol::dynamicProtocol(){
    QString algName = "algName";
    QString algDescr = "algDescription";
    QList<algorithms::AbstractAlgorithm::AlgorithmParameter> paramList;
    QList<QString> algParameters;
    int clusterNum = 1;
    QString algDylp = "dylp";
    QString algDyfn = "dyfn";
    algorithms::UserDefinedAlgorithm *myAlg = new algorithms::UserDefinedAlgorithm(paramList,algName,algDescr,algDylp,algDyfn);

    QString protName = "protName";
    QString protDescr = "protDescription";
    QList<romeo::model::protocols::features::AbstractFeature*> feat;
    bool testProtocol = false;

    DynamicProtocol *dp = new DynamicProtocol(protName,protDescr,myAlg,clusterNum,algParameters,feat,testProtocol);
    QCOMPARE(protName,dp->getName());
    QCOMPARE(protDescr,dp->getDescription());
    QCOMPARE(algName,dp->getAlgorithmName());
    QCOMPARE(testProtocol,dp->getTest());
    QCOMPARE(DYNAMIC,dp->getType());
    QCOMPARE(clusterNum,dp->getNClusters());
    QCOMPARE(algParameters,dp->getAlgorithmParameters());

    delete myAlg;
    delete dp;
}

void TestDynamicProtocol::setNClusters(){
    DynamicProtocol *dp = createProtocol();
    int clusterNum = 5;
    dp->setNClusters(clusterNum);
    QCOMPARE(clusterNum,dp->nClusters);
    delete dp;
}

void TestDynamicProtocol::setAlgorithmParameters(){
    DynamicProtocol *dp = createProtocol();
    QList<QString> algParameters;
    algParameters.append(QString("param1"));
    algParameters.append(QString("param2"));
    dp->setAlgorithmParameters(algParameters);
    QCOMPARE(algParameters,dp->algorithmParameters);
    delete dp;
}

void TestDynamicProtocol::getFeaturesName(){
    DynamicProtocol *dp = createProtocol();
    QStringList emptyList;
    QCOMPARE(emptyList,dp->getFeaturesName());
    delete dp;
}

void TestDynamicProtocol::read2DVideo(){
    DynamicProtocol *dp = createProtocol();
    cv::VideoCapture *video = new cv::VideoCapture();
    QVERIFY(dp->read2DVideo(*video) != 0);
    delete video;
    delete dp;
}

void TestDynamicProtocol::read3DVideo(){
    /*QDir dataTest = QDir::current();
    dataTest.cd("..");
    dataTest.cd("..");
    dataTest.cd("tests");
    typedef itk::Image<itk::RGBPixel<unsigned char>,4> Image4DType;

    QString name="NomeDataset";
    QString fileSubject=dataTest.absolutePath().append("/images/image.tif");
    QString mask=dataTest.absolutePath().append("/images/mask.tif");

    DynamicProtocol *dp = createProtocol();
    romeo::model::imageIO::HandlerIODynamic* videoHandler = romeo::model::imageIO::HandlerIODynamic::getInstance();
    Image4DType::Pointer video = videoHandler->readImage<Image4DType::Pointer,Image4DType>(fileSubject);
    QVERIFY(dp->read3DVideo(video) != 0);
    delete video;
    delete dp;*/
}

/*void TestDynamicProtocol::apply2DDynamicFeature(){
    DynamicProtocol *dp = createProtocol();
    cv::VideoCapture *video = new cv::VideoCapture();
    QVERIFY(dp->read2DVideo(*video) != 0);
    delete video;
    delete dp;
}

void TestDynamicProtocol::apply3DDynamicFeature(){
    DynamicProtocol *dp = createProtocol();
    cv::VideoCapture *video = new cv::VideoCapture();
    QVERIFY(dp->read2DVideo(*video) != 0);
    delete video;
    delete dp;
}
*/
