/**
* \file dataset3dt.cpp
* \author Matteo Pozza
* \date 2014-02-17
**
* \brief Header della classe Dataset3DT del package romeo::model::datasets
*/


#include "dataset3dt.h"
#include "subject3dt.h"
#include <src/romeo/model/imageIO/handleriodynamic.h>
using namespace romeo::model::datasets;
using namespace romeo::model;
using namespace romeo::model::protocols;
using namespace romeo::model::imageIO;
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

QString Dataset3DT::checkSubject(QString &fileSubject, QString &mask) {
    QString messageToReturn = "";
    // l'immagine deve essere un'immagine 4D
    // la maschera deve essere una immagine 3D
    typedef itk::RGBPixel<unsigned char> RGBPixelType;
    typedef itk::Image<RGBPixelType,4> ImageType;
    typedef itk::Image<unsigned char,3> MaskType;
    romeo::model::imageIO::HandlerIODynamic* imageHandler = romeo::model::imageIO::HandlerIODynamic::getInstance();
    try {
        imageHandler->readImage<ImageType::Pointer,ImageType>(fileSubject);
    }
    catch(itk::ExceptionObject & e) {
        messageToReturn = "There were problems in reading the image to analyze";
    }
    try {
        imageHandler->readImage<MaskType::Pointer,MaskType>(mask);
    }
    catch(itk::ExceptionObject & e) {
        if(messageToReturn == "") {
            messageToReturn = "There were problems in reading the mask";
        }
        else {
            messageToReturn += " and its mask"
        }
    }
    if(messageToReturn == "") {
        messageToReturn = "Ok";
        return messageToReturn;
    }
    else {
        messageToReturn += ". Please check the paths of your subject.";
        return messageToReturn;
    }
}
