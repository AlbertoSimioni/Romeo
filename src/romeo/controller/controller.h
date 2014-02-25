/**
* \file controller.h
* \author Matteo Pozza
* \date 2014-02-17
**
* \brief Header della classe Controller del package romeo::controller
*/


#ifndef CONTROLLER_H
#define CONTROLLER_H

#include<QObject>
#include<src/romeo/view/viewmanager.h>
#include<src/romeo/model/core/modelcore.h>
#include<src/romeo/model/protocols/algorithms/algorithmslist.h>
#include<src/romeo/model/protocols/features/featureslist.h>
#include<src/romeo/view/mainWindow/mainwindow.h>
#include<src/romeo/model/protocols/protocolslist.h>
#include<src/romeo/view/dialogs/protocoldialog.h>
#include<src/romeo/view/dialogs/newdatasetdialog.h>
#include<src/romeo/view/dialogs/protocoldialog.h>
#include<src/romeo/view/dialogs/newalgorithmdialog.h>
#include<src/romeo/view/dialogs/newfeaturedialog.h>
#include<src/romeo/view/dialogs/executedialog.h>
#include<src/romeo/view/dialogs/addsubjectdialog.h>
#include<src/romeo/view/dialogs/algorithmslistdialog.h>
#include<src/romeo/view/dialogs/featureslistdialog.h>
#include<src/romeo/view/mainWindow/datasetsexplorer.h>
#include<src/romeo/view/mainWindow/protocolsexplorer.h>

namespace romeo {
namespace controller{

/**
 * \brief La classe Controller da completare
 *
 * Descrizione dettagliata
 */

//BISOGNA ASSOLUTAMENTE SPEZZARLA IN PIù CLASSI, HA TROPPO CAMPI ORA
class Controller : public QObject
{
        Q_OBJECT
public:
    /*!
     * \brief Metodo statico che ritorna l'istanza del controller, in caso sia la prima volta ad essere invocato
     *  si preoccupa anche di costruire l'istanza.
     */
    static Controller* getInstance(QObject* parent = 0);

    ~Controller();

public slots:
    void viewNewDatasetDialog();
    void viewNewProtocolDialog();
    void viewNewAlgorithmDialog();
    void viewNewFeatureDialog();
    void viewAlgorithmsListDialog();
    void viewFeaturesListDialog();
    /*!
     * \brief Controlla se il nome del protocollo passato in input è già impegnato da un protocollo e in caso si preoccupa di
     * di far visualizzare un messaggio di errore sul wizard di creazione di un protocollo
     */
    void checkProtocolName(QString protocolName);
    /*!
     * \brief Controlla se il nome dell'algoritmo passato in input è già impegnato da un algoritmo e in caso si preoccupa di
     * di far visualizzare un messaggio di errore sul dialogo di creazione di un algoritmo
     */
    void checkAlgorithmName(QString algorithmName);

    /*!
     * \brief Controlla se il nome dell'algoritmo passato in input è già impegnato da una feature e in caso si preoccupa di
     * di far visualizzare un messaggio di errore sul dialogo di creazione di una feature
     */
    void checkFeatureName(QString featureName);

    void checkDatasetName(QString datasetName);

    /*!
     * \brief Slot connesso con il segnale createProtocol della classe ProtocolDialog, crea un nuovo protocollo con i parametri in input
     * \param protocolName
     * \param desc
     * \param test
     * \param features
     * \param algorithm
     * \param type
     * \param windowSize
     * \param distanceGLCM
     */
    void addProtocol(QString protocolName,QString desc,bool test,QList<QString>features,QString algorithm,romeo::model::protocols::ProtocolType type,int windowSize,int distanceGLCM);
    /*!
     * \brief Slot connesso con il segnale createAlgorithm della classe NewAlgorithmDialog, crea un nuovo algoritmo con i parametri in input
     */
    void addAlgorithm(QString name,QString desc, QString dyfn, QString dylp,QList<romeo::model::protocols::algorithms::AbstractAlgorithm::AlgorithmParameter> parameters);

    void addFeature(QString name,QString desc,QString dyfn,QString dylp,romeo::model::protocols::features::FeatureType type);

    void addDataset(QString name, romeo::model::InputFormat type);
private:

    /*!
     * \brief Campo dati statico che contiene il riferimento all'unica istanza del controller
     */
    static Controller* instance;


    /*!
     * \brief Costruttore privato del controller, poiché la classe Controller implementa il design pattern singleton
     */
    Controller(QObject* parent = 0);


    /*!
     * \brief Metodo che collega i segnali emessi dalle varie view agli slot presenti nel controller
     */
    void connectViewsSignals();


    /*!
     * \brief Riferimento alla classe facade della view, essa mette a disposizione i metodi per gestire
     * l'apertura delle finestre di dialogo
     */
    //romeo::view::ViewManager* viewManager;


    /*!
     * \brief Riferimento alla finestra principale del programma
     */
    romeo::view::mainWindow::MainWindow* mainWindow;

    /*!
      * \brief Riferimento al dialogo di aggiunta subject
      */
     romeo::view::dialogs::NewDatasetDialog* newDatasetDialog;

     /*!
      * \brief Riferimento al dialogo per l'aggiunta o la modifica di un protocollo
      */
     romeo::view::dialogs::ProtocolDialog* protocolDialog;

     /*!
      * \brief Riferimento al dialogo per l'aggiunta di una nuova feature
      */
     romeo::view::dialogs::NewFeatureDialog* newFeatureDialog;

     /*!
      * \brief Riferimento al dialogo per l'aggiunta di un nuovo algoritmo
      */
     romeo::view::dialogs::NewAlgorithmDialog* newAlgorithmDialog;

     /*!
      * \brief Riferimento al dialogo per l'aggiunta di un nuovo subject
      */
     romeo::view::dialogs::AddSubjectDialog* addSubjectDialog;

     /*!
      * \brief Riferimento al dialogo per l'esecuzione di un protocollo
      */
     romeo::view::dialogs::ExecuteDialog* executeDialog;

     /*!
      * \brief Riferimento al dialogo per la visualizzazione della lista della feature
      */
     romeo::view::dialogs::FeaturesListDialog* featuresListDialog;

     /*!
      * \brief Riferimento al dialogo per la visualizzazione della lista degli algoritmi di clustering
      */
     romeo::view::dialogs::AlgorithmsListDialog* algorithmsListDialog;

     /*!
      * \brief Riferimento al widget che mostra la lista dei dataset del programma
      */
     romeo::view::mainWindow::DatasetsExplorer* datasetsExplorer;

     /*!
      * \brief Riferimento al Widget che mostra la lista dei protocolli del programma
      */
     romeo::view::mainWindow::ProtocolsExplorer* protocolsExplorer;






     romeo::model::protocols::algorithms::AlgorithmsList* algorithmsList;

     romeo::model::protocols::features::FeaturesList* featuresList;

     romeo::model::protocols::ProtocolsList* protocolsList;

     romeo::model::datasets::DatasetsList* datasetsList;

     romeo::model::core::ModelCore* modelCore;
};
}}
#endif // CONTROLLER_H
