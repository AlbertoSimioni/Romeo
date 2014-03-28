#include "handleriodynamic.h"
//QT
#include <QDebug>

using namespace romeo::model::imageIO;

HandlerIODynamic* HandlerIODynamic::instance=0;
HandlerIODynamic *HandlerIODynamic::getInstance()
{
    if(instance == 0)
    {
        instance= new HandlerIODynamic();
    }
    return instance;
}


HandlerIODynamic::HandlerIODynamic()
{
}

cv::VideoCapture HandlerIODynamic::read2DVideo(QString path) {
    cv::VideoCapture videoCapture( path.toStdString() );
    if(!videoCapture.isOpened()) {
        throw false;
    }
    return videoCapture;
}
