/**
* \file featurescontroller.h
* \author Matteo Pozza
* \date 2014-02-17
**
* \brief Header della classe FeaturesController del package romeo::controller
*/


#ifndef FEATURESCONTROLLER_H
#define FEATURESCONTROLLER_H

#include <QObject>
#include <src/romeo/view/mainWindow/mainwindow.h>
#include <src/romeo/view/dialogs/featureslistdialog.h>
#include<src/romeo/view/dialogs/newfeaturedialog.h>
#include <src/romeo/model/protocols/features/featureslist.h>

namespace romeo {
namespace controller{

class FeaturesController : public QObject
{
    Q_OBJECT
public:
    explicit FeaturesController(view::mainWindow::MainWindow *mainw, QObject *parent = 0);
    /*!
     * \brief Metodo statico che ritorna l'istanza del controller, in caso sia la prima volta ad essere invocato
     *  si preoccupa anche di costruire l'istanza.
     */
    static FeaturesController* getInstance(romeo::view::mainWindow::MainWindow* mainw = 0,QObject* parent = 0);
private slots:

    /*!
     * \brief Inserisce nell'applicazione una nuova feature che l'utente può utilizzare nei protocolli.
     * \param name Nome della feature da aggiungere.
     * \param desc Descrizione testuale della feature.
     * \param dyfn Percorso alla libreria dinamica contenente il codice della feature.
     * \param dylp Nome della funzione con cui invocare il metodo di estrazione contenuto nella libreria dinamica.
     * \param type Tipo di feature.
     */
    void addFeature(QString name,QString desc,QString dyfn,QString dylp,romeo::model::protocols::features::FeatureType type);

    /*!
     * \brief Controlla se il nome dell'algoritmo passato in input è già impegnato da una feature e in caso si preoccupa
     * di far visualizzare un messaggio di errore sul dialogo di creazione di una feature
     */
    void checkFeatureName(QString featureName);



    /*!
     * \brief Slot pubblico che visualizza una nuova finestra di dialogo contenente un FeaturesListDialog.
     */
    void viewFeaturesListDialog();

    /*!
     * \brief Slot pubblico che visualizza una nuova finestra di dialogo contenente un NewFeatureDialog.
     */
    void viewNewFeatureDialog();
private:

    /*!
     * \brief Metodo che collega i segnali emessi dalle varie view agli slot presenti nel controller
     */
    void connectViewsSignals();
    /*!
     * \brief Campo dati statico che contiene il riferimento all'unica istanza del controller
     */
    static FeaturesController* instance;

    romeo::view::mainWindow::MainWindow* mainWindow;
    /*!
     * \brief Riferimento al dialogo per la visualizzazione della lista della feature
     */
    romeo::view::dialogs::FeaturesListDialog* featuresListDialog;

    /*!
     * \brief Riferimento al dialogo per l'aggiunta di una nuova feature
     */
    romeo::view::dialogs::NewFeatureDialog* newFeatureDialog;
    /*!
    * \brief Puntatore all'unica istanza di FeaturesList.
    */
   romeo::model::protocols::features::FeaturesList* featuresList;

};
}}
#endif // FEATURESCONTROLLER_H
