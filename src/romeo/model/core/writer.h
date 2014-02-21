/**
* \file writer.h
* \author Matteo Pozza
* \date 2014-02-17
**
* \brief Header della classe Writer del package romeo::model::core
*/

#ifndef WRITER_H
#define WRITER_H

namespace romeo {
namespace model {
namespace core{

/**
 * \brief La classe Writer da completare
 *
 * Descrizione dettagliata
 */

class Writer
{
public:
    /*!
     * \brief Metodo statico che ritorna l'istanza del Writer, in caso sia la prima volta ad essere invocato
     *  si preoccupa anche di costruire l'istanza.
     */
    static Writer* getInstance();
private:
    /*!
     * \brief Costruttore privato, poiché la classe Writer implementa il design pattern singleton
     */
    Writer();

    /*!
     * \brief Campo dati statico che contiene il riferimento all'unica istanza del Writer
     */
    static Writer* instance;
};


}}}

#endif // WRITER_H
