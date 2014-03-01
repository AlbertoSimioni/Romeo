#include "dataset3dt.h"
#include "subject3dt.h"
using namespace romeo::model::datasets;
using namespace romeo::model;
using namespace romeo::model::protocols;
Dataset3DT::Dataset3DT(QString &name): AbstractDataset(name)
{
}

AbstractSubject *Dataset3DT::makeSubject(QString &name, QString &fileSubject, QString &mask)
{
    return new Subject3DT(name, fileSubject, mask);
}


InputFormat Dataset3DT::getType(){
    return TYPE3DT;
}

ProtocolType Dataset3DT::getProtocolsType(){
    return DYNAMIC;
}
