/**
* \file datasetexplorer.h
* \author Alessandro Strenghetto
* \date 2014-02-17
**
* \brief Header della classe DatasetExplorer del package romeo::view::mainWindow
*/

#ifndef DATASETSEXPLORER_H
#define DATASETSEXPLORER_H

#include <QWidget>
#include <src/romeo/model/datasets/datasetslist.h>
#include <QTreeWidgetItem>
namespace Ui {
class DatasetsExplorer;
}

namespace romeo{
namespace view{
namespace mainWindow{

class DatasetsExplorer : public QWidget
{
    Q_OBJECT

public:
    explicit DatasetsExplorer(QWidget *parent = 0);
    ~DatasetsExplorer();

    /*!
     * \brief Ritorna il riferimento alla lista dei dataset presente nel modello
     */
    romeo::model::datasets::DatasetsList *getDatasetsList() const;
    /*!
     * \brief Permette di impostare e cambiare la lista di dataset da utilizzare
     */
    void setDatasetsList(romeo::model::datasets::DatasetsList *value);


signals:
    /*!
     * \brief Segnala la volontà dell'utente di cambiare il dataset correntemente selezionato, come attributo contiene il nome del nuovo dataset
     */
    void currentDatasetChanged(QString name);
private slots:
    /*!
     * \brief Riempie o aggiorna la lista dei dataset con i dataset presenti nel modello
     */
    void fillDatasetsExplorer();
    /*!
     * \brief Slot avviato al doppio click da parte dell'utente di un elemento all'interno della lista dei dataset, richiede in input l'item premuto
     */
    void onItemDoubleClicked(QTreeWidgetItem* item);


private:

    void connectUI();

    Ui::DatasetsExplorer *ui;
    /*!
     * \brief Riferimento alla lista di dataset presente nel model
     */
    romeo::model::datasets::DatasetsList* datasetsList;
};
}}}
#endif // DATASETSEXPLORER_H
