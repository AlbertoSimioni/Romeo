/**
* \file dataset3d.cpp
* \author Matteo Pozza
* \date 2014-02-17
**
* \brief Header della classe Dataset3D del package romeo::model::datasets
*/


#include "dataset3d.h"
#include "subject3d.h"
using namespace romeo::model::datasets;
using namespace romeo::model;
using namespace romeo::model::protocols;
Dataset3D::Dataset3D(QString &name): AbstractDataset(name)
{
}

AbstractSubject *Dataset3D::makeSubject(QString &name, QString &fileSubject, QString &mask)
{
    return new Subject3D(name, fileSubject, mask);
}

InputFormat Dataset3D::getType(){
    return TYPE3D;
}


ProtocolType Dataset3D::getProtocolsType(){
    return STATIC;
}



QString Dataset3D::checkSubject(QString &fileSubject, QString &mask){

}
