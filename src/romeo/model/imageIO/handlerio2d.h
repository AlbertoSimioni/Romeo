/**
* \file handlerio2d.h
* \author Matteo Pozza
* \date 2014-02-17
**
* \brief Header della classe HandlerIO2D del package romeo::model::core
*/
#ifndef HANDLERIO2D_H
#define HANDLERIO2D_H
#include"handlerio.h"
namespace romeo {
namespace model {
namespace imageIO{

/**
 * \brief La classe HandlerIO2D da completare
 *
 * Descrizione dettagliata
 */



class HandlerIO2D : public HandlerIO
{
public:
    static HandlerIO2D* getInstance();
private:
    /*!
     * \brief Costruttore privato, poiché la classe HandlerIO2D implementa il design pattern singleton
     */
    HandlerIO2D();

    /*!
     * \brief Campo dati statico che contiene il riferimento all'unica istanza di HandlerIO2D
     */
    static HandlerIO2D* instance;
};
}}}
#endif // HANDLERIO2D_H
