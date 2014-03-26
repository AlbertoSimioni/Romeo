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

#include<src/romeo/view/mainWindow/mainwindow.h>
#include<src/romeo/view/dialogs/newdatasetdialog.h>
#include<src/romeo/view/dialogs/addsubjectdialog.h>

#include<src/romeo/view/mainWindow/datasetsexplorer.h>
#include<src/romeo/view/mainWindow/executepanel.h>
#include<src/romeo/view/mainWindow/subjectspanel.h>



namespace romeo {
namespace controller{

/**
 * \brief La classe MainController da completare
 *
 * Descrizione dettagliata
 */


class DatasetsController : public QObject
{
        Q_OBJECT
public:
    /*!
     * \brief Metodo statico che ritorna l'istanza del controller, in caso sia la prima volta ad essere invocato
     *  si preoccupa anche di costruire l'istanza.
     */
    static DatasetsController* getInstance(QObject* parent = 0);

    ~DatasetsController();

    romeo::view::mainWindow::MainWindow *getMainWindow() const;

public slots:
    /*!
     * \brief Slot pubblico che visualizza una nuova finestra di dialogo contenente un NewDatasetDialog.
     */
    void viewNewDatasetDialog();



    /*!
     * \brief Slot pubblico che visualizza una nuova finestra di dialogo contenente un AddSubjectDialog.
     */
    void viewAddSubjectDialog();


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
     * \brief Slot che elimina dal model il dataset corrente, recupera il primo dataset dalla lista dei dataset e lo fa diventare il dataset corrente.
     */
    void deleteCurrentDataset();

    /*!
     * \brief Slot che elimina dal dataset corrente il subject che ha come nome il parametro in input
     */
    void deleteSubject(QString subjectName);


private:

    /*!
     * \brief Campo dati statico che contiene il riferimento all'unica istanza del controller
     */
    static DatasetsController* instance;


    /*!
     * \brief Costruttore privato del controller, poiché la classe Controller implementa il design pattern singleton
     */
    DatasetsController(QObject* parent = 0);


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
      * \brief Riferimento al dialogo per l'aggiunta di un nuovo subject
      */
     romeo::view::dialogs::AddSubjectDialog* addSubjectDialog;

     /*!
      * \brief Riferimento al widget che mostra la lista dei dataset del programma
      */
     romeo::view::mainWindow::DatasetsExplorer* datasetsExplorer;


     /*!
      * \brief Riferimento al Widget che mostra il panello con la lista dei subject associati al dataset corrente
      */
     romeo::view::mainWindow::SubjectsPanel* subjectsPanel;

     /*!
      * \brief Puntatore all'unica istanza di DatasetsList.
      */
     romeo::model::datasets::DatasetsList* datasetsList;

};
}}
#endif // CONTROLLER_H
