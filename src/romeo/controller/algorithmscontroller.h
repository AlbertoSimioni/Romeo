
/**
* \file algorithmscontroller.h
* \author Matteo Pozza
* \date 2014-02-17
**
* \brief Header della classe AlgorithmsController del package romeo::controller
*/

#ifndef ALGORITHMSCONTROLLER_H
#define ALGORITHMSCONTROLLER_H

#include <QObject>
#include <src/romeo/view/mainWindow/mainwindow.h>
#include <src/romeo/view/dialogs/algorithmslistdialog.h>
#include<src/romeo/view/dialogs/newalgorithmdialog.h>
#include <src/romeo/model/protocols/algorithms/algorithmslist.h>

namespace romeo {
namespace controller{

class AlgorithmsController : public QObject
{
    Q_OBJECT
public:
    explicit AlgorithmsController(romeo::view::mainWindow::MainWindow* mainw = 0,QObject *parent = 0);

    /*!
     * \brief Metodo statico che ritorna l'istanza del controller, in caso sia la prima volta ad essere invocato
     *  si preoccupa anche di costruire l'istanza.
     */
    static AlgorithmsController* getInstance(romeo::view::mainWindow::MainWindow* mainw = 0,QObject* parent = 0);
private slots:
    /*!
     * \brief Controlla se il nome dell'algoritmo passato in input è già impegnato da un algoritmo e in caso si preoccupa di
     * di far visualizzare un messaggio di errore sul dialogo di creazione di un algoritmo
     */
    void checkAlgorithmName(QString algorithmName);

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
     * \brief Slot pubblico che visualizza una nuova finestra di dialogo contenente un NewAlgorithmDialog.
     */
    void viewNewAlgorithmDialog();

    /*!
     * \brief Slot pubblico che visualizza una nuova finestra di dialogo contenente un AlgorithmsListDialog.
     */
    void viewAlgorithmsListDialog();



private:


    /*!
     * \brief Metodo che collega i segnali emessi dalle varie view agli slot presenti nel controller
     */
    void connectViewsSignals();
    /*!
     * \brief Campo dati statico che contiene il riferimento all'unica istanza del controller
     */
    static AlgorithmsController* instance;

    romeo::view::mainWindow::MainWindow* mainWindow;

    /*!
     * \brief Riferimento al dialogo per la visualizzazione della lista degli algoritmi di clustering
     */
    romeo::view::dialogs::AlgorithmsListDialog* algorithmsListDialog;

    /*!
     * \brief Riferimento al dialogo per l'aggiunta di un nuovo algoritmo
     */
    romeo::view::dialogs::NewAlgorithmDialog* newAlgorithmDialog;

    /*!
     * \brief Puntatore all'unica istanza di AlgorithmsList.
     */
    romeo::model::protocols::algorithms::AlgorithmsList* algorithmsList;

};


}}

#endif // ALGORITHMSCONTROLLER_H
