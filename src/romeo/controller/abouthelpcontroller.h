
/**
* \file abouthelpcontroller.h
* \author Matteo Pozza
* \date 2014-02-17
**
* \brief Header della classe AboutHelpController del package romeo::controller
*/


#ifndef ABOUTHELPCONTROLLER_H
#define ABOUTHELPCONTROLLER_H

#include <QObject>
#include <src/romeo/view/mainWindow/mainwindow.h>
#include<src/romeo/view/dialogs/helpdialog.h>
#include<src/romeo/view/dialogs/aboutdialog.h>
namespace romeo {
namespace controller{

/**
 * \brief La classe MainController da completare
 *
 * Descrizione dettagliata
 */


class AboutHelpController : public QObject
{
    Q_OBJECT
public:
    explicit AboutHelpController(romeo::view::mainWindow::MainWindow* mainw = 0,QObject *parent = 0);


    /*!
     * \brief Metodo statico che ritorna l'istanza del controller, in caso sia la prima volta ad essere invocato
     *  si preoccupa anche di costruire l'istanza.
     */
    static AboutHelpController* getInstance(romeo::view::mainWindow::MainWindow* mainw = 0,QObject* parent = 0);

private slots:

    /*!
     * \brief Mostra il manuale utente in una finestra separata
     */
    void viewHelpDialog();
    /*!
     * \brief Mostra una finestra con le informazioni riguardanti l'applicazione
     */
    void viewAboutDialog();


private:
    /*!
     * \brief Metodo che collega i segnali emessi dul dialogo di esecuzioni agli slot della classe
     */
    void connectViewsSignals();


    /*!
     * \brief Campo dati statico che contiene il riferimento all'unica istanza del controller
     */
    static AboutHelpController* instance;



    romeo::view::mainWindow::MainWindow* mainWindow;

    /*!
     * \brief Puntatore alla finestra di dialogo
     */
    romeo::view::dialogs::HelpDialog* helpDialog;
    /*!
     * \brief Puntatore alla finestra con le informazioni sull'applicazione
     */
    romeo::view::dialogs::AboutDialog* aboutDialog;
};
}}

#endif // ABOUTHELPCONTROLLER_H
