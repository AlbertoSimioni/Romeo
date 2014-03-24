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
#include<src/romeo/view/mainWindow/executepanel.h>
#include<src/romeo/view/mainWindow/protocolspanel.h>
#include<src/romeo/view/mainWindow/subjectspanel.h>
#include<src/romeo/view/dialogs/associateprotocoldialog.h>
#include<src/romeo/view/dialogs/helpdialog.h>
#include<src/romeo/view/dialogs/aboutdialog.h>

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
    /*!
     * \brief Slot pubblico che visualizza una nuova finestra di dialogo contenente un NewDatasetDialog.
     */
    void viewNewDatasetDialog();
    /*!
     * \brief Slot pubblico che visualizza una nuova finestra di dialogo contenente un NewProtocolDialog.
     */
    void viewNewProtocolDialog();
    /*!
     * \brief Slot pubblico che visualizza una nuova finestra di dialogo contenente un NewAlgorithmDialog.
     */
    void viewNewAlgorithmDialog();
    /*!
     * \brief Slot pubblico che visualizza una nuova finestra di dialogo contenente un NewFeatureDialog.
     */
    void viewNewFeatureDialog();
    /*!
     * \brief Slot pubblico che visualizza una nuova finestra di dialogo contenente un AlgorithmsListDialog.
     */
    void viewAlgorithmsListDialog();
    /*!
     * \brief Slot pubblico che visualizza una nuova finestra di dialogo contenente un FeaturesListDialog.
     */
    void viewFeaturesListDialog();
    /*!
     * \brief Slot pubblico che visualizza una nuova finestra di dialogo contenente un AddSubjectDialog.
     */
    void viewAddSubjectDialog();
    /*!
     * \brief Slot pubblico che visualizza una nuova finestra di dialogo contenente un AssociateProtocolDialog.
     */
    void viewAssociateProtocolDialog();
    /*!
     * \brief Mostra il manuale utente in una finestra separata
     */
    void viewHelpDialog();
    /*!
     * \brief Mostra una finestra con le informazioni riguardanti l'applicazione
     */
    void viewAboutDialog();

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
     * \brief Controlla se il nome dell'algoritmo passato in input è già impegnato da una feature e in caso si preoccupa
     * di far visualizzare un messaggio di errore sul dialogo di creazione di una feature
     */
    void checkFeatureName(QString featureName);
    /*!
     * \brief Controlla se il nome dato in input sia già in uso da un dataset all'interno dell'applicazione e fa visualizzare un messaggio di errore in questo caso.
     */
    void checkDatasetName(QString datasetName);

    /*!
     * \brief controlla se il nome del subject dato in input è già in uso nel dataset corrente  e in caso si preoccupa di
     * di far visualizzare un messaggio di errore sul dialogo di creazione di un subject
     */
    void checkSubjectName(QString subjectName);

    /*!
     * \brief Slot connesso con il segnale createProtocol della classe ProtocolDialog, crea un nuovo protocollo con i parametri in input
     * \param protocolName Nome del protocollo da inserire.
     * \param desc Descrizione del protocollo.
     * \param test Parametro booleano che indica se il protocollo è di test.
     * \param features Lista delle feature che il protocollo deve eseguire.
     * \param algorithm L'algoritmo di clustering associato al protocollo.
     * \param type Il tipo di protocollo che si vuole creare.
     * \param windowSize Dimensione della finestra su cui eseguire il protocollo.
     * \param distanceGLCM Distanza dalla GLCM impostata per il protocollo.
     */
    void addProtocol(QString protocolName,QString desc,bool test,QList<QString>features,QString algorithm,romeo::model::protocols::ProtocolType type,int windowSize,int distanceGLCM,int nClusters,QList<QString> parametersValue);
    /*!
     * \brief Slot connesso con il segnale createAlgorithm della classe NewAlgorithmDialog, crea un nuovo algoritmo con i parametri in input
     * \param name Nome dell'algoritmo da aggiungere.
     * \param desc Descrizione testuale dell'algoritmo.
     * \param dylp Percorso alla libreria dinamica contenente il codice dell'a feature'algoritmo.
     * \param dyfn Nome della funzione con cui invocare il metodo contenuto nella libreria dinamica.
     * \param parameters Lista dei parametri che prende in input l'algoritmo.
     */
    void addAlgorithm(QString name,QString desc, QString dyfn, QString dylp,QList<romeo::model::protocols::algorithms::AbstractAlgorithm::AlgorithmParameter> parameters);
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
     * \brief Metodo che aggiunge un nuovo dataset all'applicazione disponibile all'utente.
     * \param name
     * \param type
     */
    void addDataset(QString name, romeo::model::InputFormat type);

    /*!
     * \brief Slot che cambia il dataset correntemente visualizzato nella view, riceve in input il nome del nuovo dataset da visualizzare
     * \param name
     */
    void changeCurrentDataset(QString name);

    /*!
     * \brief Slot che si preoccupa di creare un nuovo subject con i dati in ingresso nel dataset corrente
     * \param subjectName Nome del subject da aggiungere.
     * \param dataPath Percorso all'immagine relativa al subject.
     * \param maskPath Percorso alla maschera del subject.
     */
    void addSubject(QString subjectName, QString dataPath, QString maskPath);

    /*!
     * \brief Slot che si preoccura di associare al dataset corrente il protocollo con nome dato in input
     */
    void associateProtocol(QString protocolName);

    /*!
     * \brief Slot che elimina dal model il dataset corrente, recupera il primo dataset dalla lista dei dataset e lo fa diventare il dataset corrente.
     */
    void deleteCurrentDataset();

    /*!
     * \brief Slot che elimina dal dataset corrente il subject che ha come nome il parametro in input
     */
    void deleteSubject(QString subjectName);

    /*!
     * \brief Slot che elimina dalla lista dei protocolli il nome del protocollo dato in input e rimuove tutte le associazioni a tale protocollo nei vari dataset
     */
    void deleteProtocol(QString protocolName);

    /*!
     * \brief Slot che elimina dal dataset corrente l'associazione con il protocollo dato in input
     */
    void removeProtocolAssociation(QString protocolName);

    /*!
     * \brief Slot che riceve in input i dati per l'esecuzione e invoca l'esecuzione sul dataset corrente
     * \param protocol Nome del protocollo da eseguire.
     * \param subjects Lista contenente i soggetti su cui fare l'analisi.
     * \param resultsPath Il percorso nel file system su cui salvare i risultati.
     * \param viewResults Parametro booleano che indica se visualizzare la cartella dei risultati al tremine dell'esecuzione.
     * \param viewFeatures Flag booleana che indica se visualizzare le feature estratte durante l'esecuzione.
     * \param saveFeatures Parametro booleano che indica se salvare su disco i risultati delle feature estratte.
     * \param format Il formato delle immagini da analizzare.
     */
    void startAnalysis(QString protocol,QList<QString> subjects,QString resultsPath,bool viewResults,bool viewFeatures,bool saveFeatures,QString format);

    /*!
     * \brief Slot che si preoccupa di abortire la analisi in esecuzione sul dataset corrente
     */
    void abortAnalysis();

    /*!
     * \brief Slot che apre sul dialogo per la visualizzazione del protocollo, il protocollo con nome dato in input
     */
    void openProtocol(QString protocolName);


    void modifyProtocol(QString oldProtocolName,QString protocolName,QString desc,bool test,QList<QString>features,QString algorithm,romeo::model::protocols::ProtocolType type,int windowSize,int distanceGLCM,int nClusters,QList<QString> parametersValue);

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
      * \brief Riferimento al widget che mostra la lista dei protocolli che si possono associare al dataset corrente.
      */
     romeo::view::dialogs::AssociateProtocolDialog* associateProtocolDialog;
     /*!
      * \brief Puntatore alla finestra di dialogo
      */
     romeo::view::dialogs::HelpDialog* helpDialog;
     /*!
      * \brief Puntatore alla finestra con le informazioni sull'applicazione
      */
     romeo::view::dialogs::AboutDialog* aboutDialog;



     /*!
      * \brief Riferimento al widget che mostra la lista dei dataset del programma
      */
     romeo::view::mainWindow::DatasetsExplorer* datasetsExplorer;

     /*!
      * \brief Riferimento al Widget che mostra la lista dei protocolli del programma
      */
     romeo::view::mainWindow::ProtocolsExplorer* protocolsExplorer;

     /*!
      * \brief Riferimento al Widget che mostra il panello per eseguire un protocollo
      */
     romeo::view::mainWindow::ExecutePanel* executePanel;
     /*!
      * \brief Riferimento al Widget che mostra il panello con la lista dei protocolli associati al dataset corrente
      */
     romeo::view::mainWindow::ProtocolsPanel* protocolsPanel;
     /*!
      * \brief Riferimento al Widget che mostra il panello con la lista dei subject associati al dataset corrente
      */
     romeo::view::mainWindow::SubjectsPanel* subjectsPanel;
     /*!
      * \brief Puntatore all'unica istanza di AlgorithmsList.
      */
     romeo::model::protocols::algorithms::AlgorithmsList* algorithmsList;
     /*!
      * \brief Puntatore all'unica istanza di FeaturesList.
      */
     romeo::model::protocols::features::FeaturesList* featuresList;
     /*!
      * \brief Puntatore all'unica istanza di ProtocolsList.
      */
     romeo::model::protocols::ProtocolsList* protocolsList;
     /*!
      * \brief Puntatore all'unica istanza di DatasetsList.
      */
     romeo::model::datasets::DatasetsList* datasetsList;
     /*!
      * \brief Puntatore all'unica istanza di ModelCore.
      */
     romeo::model::core::ModelCore* modelCore;
};
}}
#endif // CONTROLLER_H
