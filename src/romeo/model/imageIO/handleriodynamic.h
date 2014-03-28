#ifndef HANDLERIODYNAMIC_H
#define HANDLERIODYNAMIC_H
//ITK
#include "itkOpenCVImageBridge.h"
//PROGRAMMA
#include <src/romeo/model/imageIO/handlerio.h>

namespace romeo {
namespace model {
namespace imageIO{

class HandlerIODynamic : public HandlerIO
{
public:
    /*!
     * \brief Ritorna l'unica istanza di HandlerIODynamic.
     */
    static HandlerIODynamic* getInstance();
    /*!
     * \brief Metodo che legge da disco un video 2D e ritorna un puntatore di OpenCV ad esso.
     * \param path Percorso al file video da caricare.
     */
    cv::VideoCapture read2DVideo(QString path);

private:
    /*!
     * \brief Costruttore privato, poiché la classe HandlerIODynamic implementa il design pattern singleton
     */
    HandlerIODynamic();
    /*!
     * \brief Campo dati statico che contiene il riferimento all'unica istanza di HandlerIODynamic
     */
    static HandlerIODynamic* instance;
};
}
}
}
#endif // HANDLERIODYNAMIC_H
