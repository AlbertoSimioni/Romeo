/**
* \file protocolspanel.h
* \author Alessandro Strenghetto
* \date 2014-02-17
**
* \brief Header della classe ProtocolsPanel del package romeo::view::mainWindow
*/
#ifndef PROTOCOLSPANEL_H
#define PROTOCOLSPANEL_H

#include <QWidget>
#include <src/romeo/model/datasets/abstractdataset.h>

namespace Ui {
class ProtocolsPanel;
}
namespace romeo {
namespace view {
namespace mainWindow{
class ProtocolsPanel : public QWidget
{
    Q_OBJECT

public:
    explicit ProtocolsPanel(QWidget *parent = 0);
    ~ProtocolsPanel();

    /*!
     * \brief Ritorna il riferimento al dataset corrente
     */
    romeo::model::datasets::AbstractDataset *getCurrentDataset() const;
    /*!
     * \brief Cambia il riferimento al dataset corrente
     */
    void setCurrentDataset(romeo::model::datasets::AbstractDataset *dataset);

protected:

    //metodi per il drag & drop da commentare maggiormente
    virtual void dragEnterEvent(QDragEnterEvent * event);
    virtual void dragLeaveEvent(QDragLeaveEvent * event);
    virtual void dragMoveEvent(QDragMoveEvent * event);
    virtual void dropEvent(QDropEvent * event);

protected slots:
    /*!
     * \brief Riempie la lista degli algoritmi con gli algoritmi presenti nel modello
     */
    void fillProtocolsList();
private:
    void connectUI();
    /*!
     * \brief Slot che aggiunge un protocollo e i suoi risultati al widget che mostra la lista dei subject
     */
    void addProtocol(QString protocolName, QStringList results);

    /*!
     * \brief Riferimento al dataset attualmente attivo nella schermata
     */
    romeo::model::datasets::AbstractDataset* currentDataset;

    Ui::ProtocolsPanel *ui;
};
}}}
#endif // PROTOCOLSPANEL_H
