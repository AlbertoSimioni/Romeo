/**
* \file handleriostatic.h
* \author Matteo Pozza
* \date 2014-02-17
**
* \brief Header della classe HandlerIOStatic del package romeo::model::imageIO
*/

#ifndef HANDLERIOSTATIC_H
#define HANDLERIOSTATIC_H
#include <QString>
#include <src/romeo/model/imageIO/handlerio.h>

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
    /*!
     * \brief Ritorna l'unica istanza di HandlerIODynamic.
     */
    static HandlerIOStatic* getInstance();

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
