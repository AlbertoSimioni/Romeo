/**
* \file executepanel.h
* \author Alessandro Strenghetto
* \date 2014-02-17
**
* \brief Header della classe ExecutePanel del package romeo::view::mainWindow
*/
#ifndef EXECUTEPANEL_H
#define EXECUTEPANEL_H

#include <QWidget>

#include <src/romeo/model/datasets/abstractdataset.h>

namespace Ui {
class ExecutePanel;
}
namespace romeo{
namespace view {
namespace mainWindow{
class ExecutePanel : public QWidget
{
    Q_OBJECT

public:
    explicit ExecutePanel(QWidget *parent = 0);
    ~ExecutePanel();


    /*!
     * \brief Cambia il riferimento al dataset corrente
     */
    void setCurrentDataset(romeo::model::datasets::AbstractDataset *dataset);

signals:
    /*!
     * \brief Segnale emesso per segnale la volontà dell'utente di eseguire un protocollo, contiene i campi dati necessari all'esecuzione
     */
    void executeAnalysis(QString resultsPath,bool viewResults,bool viewFeatures,bool saveFeatures,QString format);

private slots:
    /*!
     * \brief Slot che recupera i dati della form, recupera il protocollo selezionato e i subject selezionati e invia il segnale execute analysis
     */
    void onStartClicked();

    /*!
     * \brief Slot che apre il dialogo per la selezione di una cartella dal file system e inserisce il percorso alla cartella selezionata nella linea di testo che mostra il percorso selezionato.
     */
    void onBrowseButtonClicked();

    /*!
     * \brief Slot che controlla se i dati della form che la compongono siano riempiti corretamente
     */
    void checkForm();

    /*!
     * \brief Slot avviato quando l'utente preme la check box per la visualizzazione dei risultati, se il parametro è true abilità la checkbox per la visualizzazione delle feature, altrimenti la disabilita
     */
    void onViewResultsCliked(bool state);

private:
    /*!
     * \brief Effettua le connessioni dei segnali inviati dai vari widget che compongono la classe ExecutePanel
     */
    void connectUI();

    /*!
     * \brief Riferimento al dataset attualmente attivo nella schermata
     */
    romeo::model::datasets::AbstractDataset* currentDataset;

    Ui::ExecutePanel *ui;
};
}}}
#endif // EXECUTEPANEL_H
