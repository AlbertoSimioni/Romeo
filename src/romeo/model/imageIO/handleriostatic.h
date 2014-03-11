#ifndef HANDLERIOSTATIC_H
#define HANDLERIOSTATIC_H
#include <QString>
#include <src/romeo/model/imageIO/handlerio.h>
// ITK
#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"
namespace romeo {
namespace model {
namespace imageIO{

/**
 * \brief Classe che gestisce la codifica e decodifica delle immagini statiche 2D e 3D. Inoltre è in grado di generare dalle immagini decodificate il RawData e dal RawData di rigenerare l'immagine decodificata. Inoltre la classe realizza il design pattern Singleton, poiché l'entità rappresentata non deve avere più di un'istanza.
 *
 * Implementa i metodi dichiarati nell'interfaccia ImageIO che danno la possibilità di effettuare le varie codifiche e decodifiche.
 */

class HandlerIOStatic : public HandlerIO
{
public:
    static HandlerIOStatic* getInstance();
    /*!
     *
     */
    template<typename PointerType,typename ImageType>
    PointerType readImage(QString path) {
        typedef itk::ImageFileReader< ImageType >  ReaderType;//Reader of Image Type
        typename ReaderType::Pointer reader = ReaderType::New();
        if(!path.isEmpty()) {
            reader->SetFileName(path.toStdString());
            try {
                reader->Update();
            }
            catch (itk::ExceptionObject & e) {}
            return reader->GetOutput();
        }
        else {
            PointerType emptyPointer;
            return emptyPointer;
        }
    }
    /*!
     *
     */
    template<typename PointerType,typename ImageType>
    void writeImage(PointerType output,QString fileName,QString path,QString outputFormat) {
        typedef itk::ImageFileWriter< ImageType > WriterType;
        typename WriterType::Pointer writer = WriterType::New();
        QString finalPath = path + fileName + outputFormat;
        writer->SetFileName(finalPath.toStdString());
        writer->SetInput(output);
        writer->Update();
    }

private:
    /*!
     * \brief Costruttore privato, poiché la classe HandlerIOStatic implementa il design pattern singleton
     */
    HandlerIOStatic();
    /*!
     * \brief Campo dati statico che contiene il riferimento all'unica istanza di HandlerIOStatic
     */
    static HandlerIOStatic* instance;
};
}
}
}
#endif // HANDLERIOSTATIC_H
