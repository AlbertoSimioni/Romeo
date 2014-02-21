/**
* \file settings.h
* \author Matteo Pozza
* \date 2014-02-17
**
* \brief Header della classe
*/

#ifndef SETTINGS_H
#define SETTINGS_H

namespace romeo {
namespace model {

class Settings
{
public:
    Settings();

//signals:
    /*!
     * \brief Segnale che indica che uno o più parametri dell'applicazione sono cambiati
     */
    void settingsModified();
};

}

}





#endif // SETTINGS_H
