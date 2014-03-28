/**
* \file dataset3d.cpp
* \author Matteo Pozza
* \date 2014-02-17
**
* \brief Header della classe Dataset3D del package romeo::model::datasets
*/


#include "dataset3d.h"
#include "subject3d.h"
#include <src/romeo/model/imageIO/handleriostatic.h>
using namespace romeo::model::datasets;
using namespace romeo::model;
using namespace romeo::model::protocols;
using namespace romeo::model::imageIO;
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
    QString messageToReturn = "";
    // l'immagine deve essere un'immagine 3D
    // la maschera deve essere una immagine 3D
    int numberOfPixel = 0;
    typedef itk::RGBPixel<unsigned char> RGBPixelType;
    typedef itk::Image<RGBPixelType,3> ImageType;
    typedef itk::Image<unsigned char,3> MaskType;
    romeo::model::imageIO::HandlerIOStatic* imageHandler = romeo::model::imageIO::HandlerIOStatic::getInstance();
    try {
        ImageType::Pointer imagePointer = imageHandler->readImage<ImageType::Pointer,ImageType>(fileSubject);
        numberOfPixel = imagePointer->GetLargestPossibleRegion().GetNumberOfPixels();
    }
    catch(itk::ExceptionObject & e) {
        messageToReturn += "There were problems in reading the image to analyze.\n";
    }
    if(!mask.isEmpty()) {
        try {
            MaskType::Pointer maskPointer = imageHandler->readImage<MaskType::Pointer,MaskType>(mask);
            if(numberOfPixel!=maskPointer->GetLargestPossibleRegion().GetNumberOfPixels())
                messageToReturn += "The number of pixel of the image to analyze is different from the number of pixel of its mask.\n";
        }
        catch(itk::ExceptionObject & e) {
            messageToReturn += "There were problems in reading the mask.\n";
        }
    }
    if(messageToReturn == "") {
        messageToReturn = "Ok";
        return messageToReturn;
    }
    else {
        messageToReturn += "Please check the paths of your subject.";
        return messageToReturn;
    }
}
