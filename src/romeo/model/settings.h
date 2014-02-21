/**
* \file settings.h
* \author Matteo Pozza
* \date 2014-02-17
**
* \brief Header della classe
*/

#include <QObject>

#ifndef SETTINGS_H
#define SETTINGS_H

namespace romeo {
namespace model {

class Settings: QObject
{
    Q_OBJECT
public:
    /*!
     * \brief Metodo statico che ritorna l'istanza Settings, in caso sia la prima volta ad essere invocato
     *  si preoccupa anche di costruire l'istanza.
     */
    static Settings *getInstance(QObject* parent);
private:
    /*!
     * \brief Costruttore privato, poiché la classe Settings implementa il design pattern singleton
     */
    Settings(QObject* parent=0);
    /*!
     * \brief Campo dati statico che contiene il riferimento all'unica istanza di Settings
     */
    static Settings* instance;

signals:
    /*!
     * \brief Segnale che indica che uno o più parametri dell'applicazione sono cambiati
     */
    void settingsModified();
};

}

}





#endif // SETTINGS_H
