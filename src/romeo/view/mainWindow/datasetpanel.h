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

private:
    /*!
     * \brief Riferimento al dataset attualmente attivo nella schermata
     */
    romeo::model::datasets::AbstractDataset* currentDataset;


    Ui::DatasetPanel *ui;
};
}}}
#endif // DATASETPANEL_H
