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

signals:
    /*!
     * \brief Segnale emesso quando l'utente effettua un'azione di drag & drop per l'associazione di un nuovo protocollo
     * \param name
     */
    void associateProtocol(QString protocolName);
    /*!
     * \brief Segnale emesso quando l'utente seleziona un protocollo e preme il tasto delete per eliminare l'associazione del protocollo al dataset corrente
     */
    void removeProtocolAssociation(QString protocolName);
    void openAssociateProtocolDialog();

protected:

    //metodi per il drag & drop da commentare maggiormente
    virtual void dragEnterEvent(QDragEnterEvent * event);
    virtual void dragLeaveEvent(QDragLeaveEvent * event);
    virtual void dragMoveEvent(QDragMoveEvent * event);
    virtual void dropEvent(QDropEvent * event);

private slots:
    /*!
     * \brief Riempie la lista degli algoritmi con gli algoritmi presenti nel modello
     */
    void fillProtocolsList();
    /*!
     * \brief Mostra la descrizione del protocollo correntemente selezionato
     */
    void changeDescription();
    /*!
     * \brief Recupera il percorso al risultato correntemente selezionato e apre il gestore delle cartelle a tale percorso
     */
    void openResultFolder();

    /*!
     * \brief Slot che recupera il nome del protocollo correntemente selezionato e in caso esista emette il segnale removeProtocolAssociation
     */
    void onDeleteClicked();

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
