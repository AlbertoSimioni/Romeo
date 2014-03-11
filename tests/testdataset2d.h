#ifndef TESTDATASET2D_H
#define TESTDATASET2D_H

#include <QtTest>
//#define private public
#include <../src/romeo/model/datasets/dataset2d.h>

using namespace romeo::model::datasets;

#ifndef INPUTFORMAT_H
#define INPUTFORMAT_H
Q_DECLARE_METATYPE(romeo::model::InputFormat);
#endif

#ifndef PROTOCOLTYPE_H
#define PROTOCOLTYPE_H
Q_DECLARE_METATYPE(romeo::model::protocols::ProtocolType);
#endif


class TestDataset2D : public QObject{
    Q_OBJECT

public:
    explicit TestDataset2D(QObject *parent = 0);

private slots:
   void makeSubject();
   void makeSubject_data();
   void getType();
   void getType_data();
   void getProtocolsType();
   void getProtocolsType_data();
};


#endif // TESTDATASET2D_H