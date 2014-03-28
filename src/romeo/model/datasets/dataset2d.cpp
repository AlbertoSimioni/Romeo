/**
* \file dataset2d.cpp
* \author Matteo Pozza
* \date 2014-02-17
**
* \brief Header della classe Dataset2D del package romeo::model::datasets
*/

#include "dataset2d.h"
#include "subject2d.h"
#include <src/romeo/model/imageIO/handleriostatic.h>
using namespace romeo::model::datasets;
using namespace romeo::model;
using namespace romeo::model::protocols;
using namespace romeo::model::imageIO;
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
    QString messageToReturn = "";
    // l'immagine deve essere un'immagine 2D
    // la maschera deve essere una immagine 2D
    typedef itk::RGBPixel<unsigned char> RGBPixelType;
    typedef itk::Image<RGBPixelType,2> ImageType;
    typedef itk::Image<unsigned char,2> MaskType;
    romeo::model::imageIO::HandlerIOStatic* imageHandler = romeo::model::imageIO::HandlerIOStatic::getInstance();
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
