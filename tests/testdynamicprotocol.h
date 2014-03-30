#ifndef TESTDYNAMICPROTOCOL_H
#define TESTDYNAMICPROTOCOL_H

#include <QtTest>
#define private public
#define protected public
#include <../src/romeo/model/protocols/dynamicprotocol.h>
#include <../src/romeo/model/protocols/algorithms/userdefinedalgorithm.h>
#include "itkImage.h"
#include "itkRGBPixel.h"
#include "itkNeighborhoodIterator.h"
#include "itkImageLinearConstIteratorWithIndex.h"
#include <opencv2/imgproc/imgproc.hpp>


using namespace romeo::model::protocols;

class TestDynamicProtocol : public QObject
{
    Q_OBJECT

public:
    explicit TestDynamicProtocol(QObject *parent = 0);
    DynamicProtocol* createProtocol();

private slots:
    void dynamicProtocol();
    void setNClusters();
    void setAlgorithmParameters();
    void getFeaturesName();
    void read2DVideo();
    void read3DVideo();
    /*void apply2DDynamicFeature();
    void apply3DDynamicFeature();*/
};


#endif // TESTDYNAMICPROTOCOL_H
