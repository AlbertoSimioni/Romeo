#ifndef TESTDATASET2DT_H
#define TESTDATASET2DT_H

#include <QtTest>
#include <../src/romeo/model/datasets/dataset2dt.h>

using namespace romeo::model::datasets;


#ifndef INPUTFORMAT
#define INPUTFORMAT
Q_DECLARE_METATYPE(romeo::model::InputFormat);
#endif

#ifndef PROTOCOLTYPE
#define PROTOCOLTYPE
Q_DECLARE_METATYPE(romeo::model::protocols::ProtocolType);
#endif


class TestDataset2DT : public QObject{
    Q_OBJECT

public:
    explicit TestDataset2DT(QObject *parent = 0);

private slots:
   void makeSubject();
   void makeSubject_data();
   void getType();
   void getType_data();
   void getProtocolsType();
   void getProtocolsType_data();
   void checkSubject();
};


#endif // TESTDATASET2DT_H
