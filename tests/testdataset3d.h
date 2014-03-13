#ifndef TESTDATASET3D_H
#define TESTDATASET3D_H

#include <QtTest>
#include <../src/romeo/model/datasets/dataset3d.h>

using namespace romeo::model::datasets;

#ifndef INPUTFORMAT
#define INPUTFORMAT
Q_DECLARE_METATYPE(romeo::model::InputFormat);
#endif

#ifndef PROTOCOLTYPE
#define PROTOCOLTYPE
Q_DECLARE_METATYPE(romeo::model::protocols::ProtocolType);
#endif


class TestDataset3D : public QObject{
    Q_OBJECT

public:
    explicit TestDataset3D(QObject *parent = 0);

private slots:
   void makeSubject();
   void makeSubject_data();
   void getType();
   void getType_data();
   void getProtocolsType();
   void getProtocolsType_data();
};


#endif // TESTDATASET3D_H
