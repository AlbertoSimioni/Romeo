/**
* \file handlerio.h
* \author Matteo Pozza
* \date 2014-02-17
**
* \brief Header della classe HandlerIO del package romeo::model::core
*/

#ifndef HANDLERIO_H
#define HANDLERIO_H
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
};
}}}
#endif // HANDLERIO_H
