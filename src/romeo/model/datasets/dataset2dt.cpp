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
    int numberOfPixel = 0;
    typedef itk::RGBPixel<unsigned char> RGBPixelType;
    typedef itk::Image<RGBPixelType,4> ImageType;
    typedef itk::Image<unsigned char,3> MaskType;
    romeo::model::imageIO::HandlerIODynamic* imageHandler = romeo::model::imageIO::HandlerIODynamic::getInstance();
    try {
        cv::VideoCapture imagePointer = imageHandler->read2DVideo(fileSubject);
        numberOfPixel = imagePointer.get( CV_CAP_PROP_FRAME_WIDTH ) * imagePointer.get( CV_CAP_PROP_FRAME_HEIGHT );
        // se è un video avrà almeno 2 frame
        int numberOfFrames = imagePointer.get(CV_CAP_PROP_FRAME_COUNT);
        if(numberOfFrames<=1)
            messageToReturn += "There were problems in reading the image to analyze.\n";
        /*cv::Mat frame;
        bool video = imagePointer.read(frame);
        video = imagePointer.read(frame);
        if(!video)
            messageToReturn += "There were problems in reading the image to analyze.\n";*/
    }
    catch(itk::ExceptionObject & e) {
        messageToReturn += "There were problems in reading the image to analyze.\n";
    }
    if(!mask.isEmpty()) {
        try {
            MaskType::Pointer maskPointer = imageHandler->readImage<MaskType::Pointer,MaskType>(mask);
            if(numberOfPixel!=maskPointer->GetLargestPossibleRegion().GetNumberOfPixels())
                messageToReturn += "The number of pixel of the frames of the image to analyze is different from the number of pixel of the mask.\n";
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
