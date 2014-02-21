/**
* \file viewmanager.h
* \author Alessandro Strenghetto
* \date 2014-02-17
**
* \brief Header della classe ViewManager del package romeo::view
*/


#ifndef VIEWMANAGER_H
#define VIEWMANAGER_H
#include<src/romeo/view/mainWindow/mainwindow.h>
#include<src/romeo/view/dialogs/newdatasetdialog.h>
#include<src/romeo/view/dialogs/protocoldialog.h>
#include<src/romeo/view/dialogs/newalgorithmdialog.h>
#include<src/romeo/view/dialogs/newfeaturedialog.h>
#include<src/romeo/view/dialogs/executedialog.h>
#include<src/romeo/view/dialogs/addsubjectdialog.h>
#include<src/romeo/view/dialogs/algorithmslistdialog.h>
#include<src/romeo/view/dialogs/featureslistdialog.h>
namespace romeo{
namespace view{

class ViewManager : public QObject
{
private:
    /*!
     * \brief Campo dati statico che contiene il riferimento all'unica istanza del ViewManager
     */
    static ViewManager* instance;
    /*!
     * \brief Riferimento alla finestra principale del programma
     */
    mainWindow::MainWindow* mainWindow;
    /*!
     * \brief Riferimento al dialogo di aggiunta subject
     */
    dialogs::NewDatasetDialog* newDatasetDialog;
    /*!
     * \brief Riferimento al dialogo per l'aggiunta o la modifica di un protocollo
     */
    dialogs::ProtocolDialog* protocolDialog;

    /*!
     * \brief Riferimento al dialogo per l'aggiunta di una nuova feature
     */
    dialogs::NewFeatureDialog* newFeatureDialog;

    /*!
     * \brief Riferimento al dialogo per l'aggiunta di un nuovo algoritmo
     */
    dialogs::NewAlgorithmDialog* newAlgorithmDialog;

    /*!
     * \brief Riferimento al dialogo per l'aggiunta di un nuovo subject
     */
    dialogs::AddSubjectDialog* addSubjectDialog;

    /*!
     * \brief Riferimento al dialogo per l'esecuzione di un protocollo
     */
    dialogs::ExecuteDialog* executeDialog;

    /*!
     * \brief Riferimento al dialogo per la visualizzazione della lista della feature
     */
    dialogs::FeaturesListDialog* featuresListDialog;

    /*!
     * \brief Riferimento al dialogo per la visualizzazione della lista degli algoritmi di clustering
     */
    dialogs::AlgorithmsListDialog* algorithmsListDialog;

    ViewManager(QObject* parent = 0);

public:
    /*!
     * \brief Metodo statico che ritorna l'istanza del ViewManager, in caso sia la prima volta ad essere invocato
     *  si preoccupa anche di costruire l'istanza.
     */
    static ViewManager* getInstance(QObject* parent = 0);

     ~ViewManager();

    /*!
     * \brief Mostra il dialogo per l'inserimento del nuovo dataset
     */
    void showNewDataset();

    /*!
     * \brief Mostra il dialogo per l'inserimento di un nuovo protocollo.
     */

    void showNewProtocol();

    /*!
     * \brief Mostra il dialogo per la modifica di un protocollo di test
     */
    void showModifyProtocol();

    /*!
     * \brief Mostra il dialogo per l'inserimento di un nuovo algoritmo di clustering
     */
    void showNewAlgorithm();

    /*!
     * \brief Mostra il dialogo per l'inserimento di un nuovo feature extractor
     */
    void showNewFeature();

    /*!
     * \brief Mostra il dialogo per l'inserimento di un nuovo subject
     */
    void showAddSubject();
    /*!
     * \brief Mostra il dialogo per la visualizzazione della lista degli algoritmi
     */
    void showAlgorithmsList();
    /*!
     * \brief Mostra il dialogo per la visualizzazione della lista delle feature
     */
    void showFeaturesList();

    /*!
     * \brief Ritorna il riferimento alla finestra principale
     */
    mainWindow::MainWindow *getMainWindow() const;
    /*!
     * \brief Ritorna il riferimento alla finestra di dialogo per aggiungere un dataset
     */
    dialogs::NewDatasetDialog *getNewDatasetDialog() const;
    /*!
     * \brief Ritorna il riferimento alla finestra di dialogo per un protocollo
     */
    dialogs::ProtocolDialog *getProtocolDialog() const;
    /*!
     * \brief Ritorna il riferimento alla finestra di dialogo per l'aggiunta di una nuova feature
     */
    dialogs::NewFeatureDialog *getNewFeatureDialog() const;
    /*!
     * \brief Ritorna il riferimento alla finestra di dialogo
     */
    dialogs::NewAlgorithmDialog *getNewAlgorithmDialog() const;
    /*!
     * \brief Ritorna il riferimento alla finestra per l'aggiunta di un nuovo subject
     */
    dialogs::AddSubjectDialog *getAddSubjectDialog() const;
    /*!
     * \brief Ritorna il riferimento alla finestra di esecuzione di un algoritmo di clustering
     */
    dialogs::ExecuteDialog *getExecuteDialog() const;
};
}}
#endif // VIEWMANAGER_H
