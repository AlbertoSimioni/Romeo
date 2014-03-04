#ifndef TESTFEATURESLIST_H
#define TESTFEATURESLIST_H

#include <QtTest>
#define private public
#include <../src/romeo/model/protocols/features/featureslist.h>
#include <../src/romeo/model/protocols/features/firstorderfeature.h>
#include <../src/romeo/model/protocols/features/secondorderfeature.h>
#include <../src/romeo/model/protocols/features/dynamicfeature.h>
#include <../src/romeo/model/protocols/algorithms/userdefinedalgorithm.h>

using namespace romeo::model::protocols::features;

#ifndef FEATURETYPE_H
#define FEATURETYPE_H
Q_DECLARE_METATYPE(FeatureType);
#endif

class TestFeaturesList : public QObject 
{
    Q_OBJECT

public:
    explicit TestFeaturesList(QObject *parent = 0);

private slots:
    void getInstance();
    void getFeature_data();
    void getFeature();
    void addFeature_data();
    void addFeature();
    void addFeatureByCopy_data();
    void addFeatureByCopy();
};


#endif // TESTFEATURESLIST_H
