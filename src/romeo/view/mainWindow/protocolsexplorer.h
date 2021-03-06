/**
* \file protocolsexplorer.h
* \author Alessandro Strenghetto
* \date 2014-02-17
**
* \brief Header della classe ProtocolsExplorer del package romeo::view::mainWindow
*/
#ifndef PROTOCOLSEXPLORER_H
#define PROTOCOLSEXPLORER_H

#include <QWidget>
#include <src/romeo/model/protocols/protocolslist.h>

namespace Ui {
class ProtocolsExplorer;
}
namespace romeo {
namespace view {
namespace mainWindow{

/*!
 * \brief Mostra all'utente la lista dei protocolli disponibili e permette di selezionarne uno da associare al dataset attualmente in uso.
 *
 * Reperisce la lista dei protocolli definiti dall'utente e restituisce le informazioni sul protocollo selezionato e da associare al dataset.
 */
class ProtocolsExplorer : public QWidget
{
    Q_OBJECT

public:
    explicit ProtocolsExplorer(QWidget *parent = 0);
    ~ProtocolsExplorer();
    /*!
     * \brief Ritorna la lista dei protocolli.
     */
    romeo::model::protocols::ProtocolsList *getProtocolsList() const;
    void setProtocolsList(romeo::model::protocols::ProtocolsList *value);

    /*!
     * \brief Ritorna il nome del protocollo correntemente selezionato, se nessun protocollo è selezionato ritorna una stringa vuota
     */
    QString getSelectedProtocolName();

    /*!
     * \brief Metodo che permette di modificare il tipo di protocolli che vengono visualizzati
     */
    void setCurrentProtocolsType(const romeo::model::protocols::ProtocolType &value);

signals:

    /*!
     * \brief Segnale inviato per notificare la volontà dell'utente di visualizzare un protocollo
     */
    void openProtocol(QString protocolName);
    void associateProtocol(QString);
    void deleteProtocol(QString);

private slots:

    void fillProtocolsExplorer();

    /*! !! slot che recupera il nome del protocollo correntemente selezionato e invia il segnale openProtocol
     * \brief onItemDoubleClicked
     */
    void onItemDoubleClicked();
    void associateProtocol();
    void deleteProtocol();

private:
    Ui::ProtocolsExplorer *ui;
    /*!
     * \brief Tipo dei protocolli correntemente visualizzati
     */
    romeo::model::protocols::ProtocolType currentProtocolsType;
    /*!
     * \brief Riferimento alla lista dei protocolli nel modello
     */
    romeo::model::protocols::ProtocolsList* protocolsList;
};
}}}
#endif // PROTOCOLSEXPLORER_H
