/**
* \file mainwindow.h
* \author Alessandro Strenghetto
* \date 2014-02-17
**
* \brief Header della classe MainWindow del package romeo::view::mainWindow
*/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "datasetsexplorer.h"
#include "protocolsexplorer.h"
#include "datasetpanel.h"
namespace Ui {
class MainWindow;
}

namespace romeo{
namespace view{
namespace mainWindow {
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    /*!
     * \brief Ritorna il riferimento al widget che mostra la lista dei dataset
     */
    DatasetsExplorer* getDatasetsExplorer();
    /*!
     * \brief Ritorna il riferimento al widget che mostra la lista dei protocolli
     */
    ProtocolsExplorer* getProtocolsExplorer();

    DatasetPanel* getDatasetPanel();



signals:
    /*!
     * \brief Segnale emesso alla pressione da parte dell'utente del tasto per l'apertura del dialogo di creazione di un nuovo dataset
     */
    void openNewDatasetDialog();
    /*!
     * \brief Segnale emesso alla pressione da parte dell'utente del tasto per l'apertura del dialogo di creazione di un nuovo protocollo
     */
    void openNewPortocolDialog();
    /*!
     * \brief Segnale emesso alla pressione da parte dell'utente del tasto per l'apertura del dialogo di creazione di un nuovo algoritmo
     */
    void openNewAlgorithmDialog();
    /*!
     * \brief Segnale emesso alla pressione da parte dell'utente del tasto per l'apertura del dialogo di creazione di una nuova feature
     */
    void openNewFeatureDialog();
    /*!
     * \brief Segnale emesso alla pressione da parte dell'utente del tasto per l'apertura del dialogo di visualizzazione delle feature del programma
     */
    void openFeaturesListDialog();
    /*!
     * \brief Segnale emesso alla pressione da parte dell'utente del tasto per l'apertura del dialogo di visualizzazione degli algoritmi del programma
     */
    void openAlgorithmsListDialog();

    /*!
     * \brief Segnale emesso per avvisare della volontà da parte dell'utente di cancellare il dataset corrente
     */
    void deleteCurrentDataset();





private:
    Ui::MainWindow *ui;
    /*!
     * \brief Il metodo collega le varie QAction della main window con l'emissione dei segnali della MainWindow
     */
    void connectActionsToSignal();
};
}}}
#endif // MAINWINDOW_H
