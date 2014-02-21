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
    Settings *getInstance(QObject* parent);
private:
    Settings(QObject* parent=0);
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
