/**
* \file modelcore.h
* \author Matteo Pozza
* \date 2014-02-17
**
* \brief  Header della classe Loader del package romeo::model::core
*/

#include <QDir>

#ifndef LOADER_H
#define LOADER_H


namespace romeo {
namespace model {
namespace core{

/**
 * \brief La classe Loader da completare
 *
 * Descrizione dettagliata
 */
class Loader
{
public:
    /*!
     * \brief Metodo statico che ritorna l'istanza del Loader, in caso sia la prima volta ad essere invocato
     *  si preoccupa anche di costruire l'istanza.
     */
    static Loader* getInstance();
    void loadDatabase(QDir& databaseFile, QHash<QString,QDir>& datasetFiles);
private:
    /*!
     * \brief Costruttore privato, poiché la classe Loader implementa il design pattern singleton
     */
    Loader();
    /*!
     * \brief Campo dati statico che contiene il riferimento all'unica istanza del Loader
     */
    static Loader* instance;
    void loadDatabase();
    //parseDataset(QString& name, QString& type);
    //parseSubject();
    //void parseAlgorithm(AbstractAlgorithm* alg, QXmlStreamReader& reader);
};
}}}

#endif // LOADER_H
