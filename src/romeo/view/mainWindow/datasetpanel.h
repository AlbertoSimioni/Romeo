/**
* \file datasetpanel.h
* \author Alessandro Strenghetto
* \date 2014-02-17
**
* \brief Header della classe DatasetPanel del package romeo::view::mainWindow
*/

#ifndef DATASETPANEL_H
#define DATASETPANEL_H

#include <QWidget>
#include <src/romeo/model/datasets/abstractdataset.h>
#include "protocolspanel.h"
#include "executepanel.h"
#include "subjectspanel.h"
#include <QMessageBox>
namespace Ui {
class DatasetPanel;
}

namespace romeo{
namespace view{
namespace mainWindow {

class DatasetPanel : public QWidget
{
    Q_OBJECT

public:
    explicit DatasetPanel(QWidget *parent = 0);
    ~DatasetPanel();


    /*!
     * \brief Ritorna il riferimento al panello che mostra la lista dei protocolli associati al dataset corrente
     */
    ProtocolsPanel* getProtocolsPanel();
    /*!
     * \brief Ritorna il riferimento al pannello che mostra la lista dei subject associati al dataset corrente
     */
    SubjectsPanel* getSubjectsPanel();
    /*!
     * \brief Ritorna il riferimento al pannello per l'esecuzione di un protocollo
     */
    ExecutePanel* getExecutePanel();

    /*!
     * \brief Ritorna il riferimento al dataset corrente
     */
    romeo::model::datasets::AbstractDataset *getCurrentDataset() const;
    /*!
     * \brief Cambia il riferimento al dataset corrente
     */
    void setCurrentDataset(romeo::model::datasets::AbstractDataset *dataset);



signals:
    /*!
     * \brief Segnale emesso per segnale la volontà dell'utente di eseguire un protocollo, contiene i campi dati necessari all'esecuzione
     */
    void executeAnalysis(QString protocol,QList<QString> subjects,QString resultsPath,bool viewResults,bool viewFeatures,bool saveFeatures,QString format);
private slots:
    /*!
     * \brief Slot che riceve le informazioni dall'execute panel per l'esecuzione del protocollo ed emette il segnale executeAnalysis aggiungendo le informazioni sul protocollo selezionato i subjects selezionati, in caso non ci siano non emette il segnale
     */
    void onExecuteclicked(QString resultsPath,bool viewResults,bool viewFeatures,bool saveFeatures,QString format);
private:
    /*!
     * \brief Riferimento al dataset attualmente attivo nella schermata
     */
    romeo::model::datasets::AbstractDataset* currentDataset;
    /*!
     * \brief Riferimento al dialogo d'errore mostrato quando l'utente prova ad avviare le analisi senza aver selezionato almeno un protocollo e un subject
     */
    QMessageBox* msgBox;

    Ui::DatasetPanel *ui;
};
}}}
#endif // DATASETPANEL_H
