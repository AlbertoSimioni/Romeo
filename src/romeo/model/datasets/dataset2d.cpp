/**
* \file dataset2d.cpp
* \author Matteo Pozza
* \date 2014-02-17
**
* \brief Header della classe Dataset2D del package romeo::model::datasets
*/

#include "dataset2d.h"
#include "subject2d.h"
using namespace romeo::model::datasets;
using namespace romeo::model;
using namespace romeo::model::protocols;
Dataset2D::Dataset2D(QString &name): AbstractDataset(name)
{
}

AbstractSubject *Dataset2D::makeSubject(QString &name, QString &fileSubject, QString &mask)
{
    return new Subject2D(name, fileSubject, mask);
}

InputFormat Dataset2D::getType(){
    return TYPE2D;
}

ProtocolType Dataset2D::getProtocolsType(){
    return STATIC;
}



QString Dataset2D::checkSubject(QString &fileSubject, QString &mask){

}
