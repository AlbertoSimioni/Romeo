/**
* \file dataset2dt.cpp
* \author Matteo Pozza
* \date 2014-02-17
**
* \brief Header della classe Dataset2DT del package romeo::model::datasets
*/

#include "dataset2dt.h"
#include "subject2dt.h"

using namespace romeo::model::datasets;
using namespace romeo::model;
using namespace romeo::model::protocols;
Dataset2DT::Dataset2DT(QString &name): AbstractDataset(name)
{
}

AbstractSubject *Dataset2DT::makeSubject(QString &name, QString &fileSubject, QString &mask)
{
    return new Subject2DT(name, fileSubject, mask);
}

InputFormat Dataset2DT::getType(){
    return TYPE2DT;
}


ProtocolType Dataset2DT::getProtocolsType(){
    return DYNAMIC;
}



QString Dataset2DT::checkSubject(QString &fileSubject, QString &mask){

}
