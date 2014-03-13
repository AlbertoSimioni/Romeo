/**
* \file associateprotocoldialog.h
* \author Alessandro Strenghetto
* \date 2014-02-17
**
* \brief Header della classe AssociateProtocolDialog del package romeo::view::dialogs
*/

#ifndef ASSOCIATEPROTOCOLDIALOG_H
#define ASSOCIATEPROTOCOLDIALOG_H

#include <QDialog>
#include <src/romeo/model/protocols/protocolslist.h>
namespace Ui {
class AssociateProtocolDialog;
}


namespace romeo {
namespace view {
namespace dialogs {

/*!
 * \brief Classe che rappresenta una finestra di dialogo che contiene la lista di tutti i protocolli che l'utente può associare al dataset corrente.
 *
 * Notifica tramite l'utilizzo di segnali l'associazione dei protocolli al dataset.
 */
class AssociateProtocolDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AssociateProtocolDialog(romeo::model::protocols::ProtocolsList* pl,QWidget *parent = 0);
    ~AssociateProtocolDialog();
    /*!
     * \brief Metodo che permette di modificare il tipo di protocolli che vengono visualizzati
     */
    void setCurrentProtocolsType(const romeo::model::protocols::ProtocolType &value);
signals:
    /*!
     * \brief Segnale emesso quando l'utente associa un nuovo protocollo
     */
    void associateProtocol(QString protocolName);
private slots:

    /*!
     * \brief Riempie la lista dei protocolli con i protocolli presenti nel modello
     */
    void fillProtocolsList();

    /*!
     * \brief Slot avviato alla pressione del tasto associate, se un protocollo è selezionato emette il segnale associateProtocol
     * e chiude il dialogo
     */
    void onAssociateClicked();

private:
    /*!
     * \brief Riferimento alla lista degli protocolli
     */
    romeo::model::protocols::ProtocolsList * protocolsList;
    /*!
     * \brief Tipo dei protocolli correntemente visualizzati
     */
    romeo::model::protocols::ProtocolType currentProtocolsType;
    /*!
     * \brief Effettua le connessioni dei segnali inviati dai vari widget che compongono la classe AssociateProtocolDialog
     */
    void connectUI();

    Ui::AssociateProtocolDialog *ui;
};

}}}

#endif // ASSOCIATEPROTOCOLDIALOG_H
