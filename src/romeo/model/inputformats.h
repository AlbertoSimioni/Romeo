/**
* \file handlerio.h
* \author Matteo Pozza
* \date 2014-02-17
**
* \brief In questo file del package romeo::model vengono inseriti dei tipi enumerazione per la gestione dei formati delle immagini utilizzati.
*/


#ifndef INPUTFORMATS_H
#define INPUTFORMATS_H

namespace romeo{
namespace model{

enum ImageFormat2D { BMP, PNG, JPEG, TIFF };
enum ImageFormat2DT{ AVI, MPEG, MJPEG };
enum ImageFormat3D{ NIFTY, ANALYZE };
enum InputFormat { TYPE2D, TYPE3D, TYPE2DT, TYPE3DT };

}
}


#endif // INPUTFORMATS_H

