/**
* \file handlerio.h
* \author Matteo Pozza
* \date 2014-02-17
**
* \brief Header della classe HandlerIO del package romeo::model::core::imageIO
*/

#ifndef HANDLERIO_H
#define HANDLERIO_H

// ITK
#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"
// QT
#include <QString>

#include "../../../romeo/model/inputformats.h"
namespace romeo {
namespace model {
namespace imageIO{

/**
 * \brief Interfaccia che rappresenta un generico gestore della codifica e decodifica delle immagini. Le classi che implementano l'interfaccia dovranno essere in grado di decodificare un'immagine, di generare il RawData, di decodificare il RawData e di codificare un'immagine.
 *
 * Definisce la segnatura dei metodi per le varie operazioni di codifica e decodifica.
 */

class HandlerIO
{
public:
    HandlerIO();
    /*!
     * \brief Metodo che legge da disco un immagine e ritorna un puntatore di ItkImage ad essa.
     * \param path Percorso al file immagine da caricare.
     */
    template<typename PointerType,typename ImageType>
    PointerType readImage(QString path) {
        typedef itk::ImageFileReader< ImageType >  ReaderType; //Reader of Image Type
        typename ReaderType::Pointer reader = ReaderType::New();
        if(!path.isEmpty()) {
            reader->SetFileName(path.toStdString());
            reader->Update(); // may throw an exception, will be handled by AbstractDataset
            return reader->GetOutput();
        }
        else {
            PointerType emptyPointer;
            return emptyPointer;
        }
    }
    /*!
     * \brief Metodo che scrive su disco un immagine passata come puntatore ad immagini di ITK
     * \param output Immagine di output da salvare su disco.
     * \param path percorso alla posizione di salvataggio.
     * \param outputFormat Formato in cui salvare l'immagine
     * \param
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
};
}}}
#endif // HANDLERIO_H
