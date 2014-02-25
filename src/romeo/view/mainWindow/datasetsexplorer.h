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


    romeo::model::datasets::DatasetsList *getDatasetsList() const;
    void setDatasetsList(romeo::model::datasets::DatasetsList *value);
private slots:
    /*!
     * \brief Riempie o aggiorna la lista dei dataset con i dataset presenti nel modello
     */
    void fillDatasetsExplorer();

private:

    void connectUI();

    Ui::DatasetsExplorer *ui;

    romeo::model::datasets::DatasetsList* datasetsList;
};
}}}
#endif // DATASETSEXPLORER_H
