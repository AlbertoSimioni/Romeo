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

    ViewManager(QObject* parent = 0);


public:
    /*!
     * \brief Metodo statico che ritorna l'istanza del ViewManager, in caso sia la prima volta ad essere invocato
     *  si preoccupa anche di costruire l'istanza.
     */
    static ViewManager* getInstance(QObject* parent = 0);

    /*!
     * \brief Mostra il dialogo per l'inserimento del nuovo dataset
     */
    void showNewDataset();


    mainWindow::MainWindow *getMainWindow() const;
    dialogs::NewDatasetDialog *getNewDatasetDialog() const;
};
}}
#endif // VIEWMANAGER_H
