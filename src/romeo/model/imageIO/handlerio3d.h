/**
* \file handlerio3d.h
* \author Matteo Pozza
* \date 2014-02-17
**
* \brief Header della classe HandlerIO3D del package romeo::model::core
*/

#ifndef HANDLERIO3D_H
#define HANDLERIO3D_H

#include"handlerio.h"
namespace romeo {
namespace model {
namespace imageIO{

/**
 * \brief La classe HandlerIO2D da completare
 *
 * Descrizione dettagliata
 */



class HandlerIO3D : public HandlerIO
{
public:
    /*!
     * \brief Metodo statico che ritorna l'istanza del HandlerIO3D, in caso sia la prima volta ad essere invocato
     *  si preoccupa anche di costruire l'istanza.
     */
    static HandlerIO3D* getInstance();

private:
    /*!
     * \brief Costruttore privato, poiché la classe HandlerIO3D implementa il design pattern singleton
     */
    HandlerIO3D();
    /*!
     * \brief Campo dati statico che contiene il riferimento all'unica istanza di HandlerIO3D
     */
    static HandlerIO3D* instance;
};
}}}
#endif // HANDLERIO3D_H
