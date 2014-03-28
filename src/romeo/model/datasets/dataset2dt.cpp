/**
* \file dataset2dt.cpp
* \author Matteo Pozza
* \date 2014-02-17
**
* \brief Header della classe Dataset2DT del package romeo::model::datasets
*/

#include "dataset2dt.h"
#include "subject2dt.h"
#include <src/romeo/model/imageIO/handleriodynamic.h>
using namespace romeo::model::datasets;
using namespace romeo::model;
using namespace romeo::model::protocols;
using namespace romeo::model::imageIO;
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
    QString messageToReturn = "";
    // l'immagine deve essere un video 2D
    // la maschera deve essere una immagine 2D
    typedef itk::Image<unsigned char,2> MaskType;
    romeo::model::imageIO::HandlerIODynamic* imageHandler = romeo::model::imageIO::HandlerIODynamic::getInstance();
    try {
        imageHandler->read2DVideo(fileSubject);
    }
    catch(bool e) {
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
