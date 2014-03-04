#ifndef TESTSTATICPROTOCOL_H
#define TESTSTATICPROTOCOL_H

#include <QtTest>
#define private public
#include <../src/romeo/model/protocols/staticprotocol.h>
#include <../src/romeo/model/protocols/algorithms/userdefinedalgorithm.h>
//#include <../src/romeo/model/protocols/features/firstorderfeature.h>

using namespace romeo::model::protocols;

class TestStaticProtocol : public QObject 
{
    Q_OBJECT

public:
    explicit TestStaticProtocol(QObject *parent = 0);
    StaticProtocol *createProtocol();

private slots:
    void staticProtocol();
    void setWindowSize();
    void setDistancetoGLCM();
    void setNClusters();
    void setAlgorithmParameters();
    void getFeaturesName();
};


#endif // TESTSTATICPROTOCOL_H
