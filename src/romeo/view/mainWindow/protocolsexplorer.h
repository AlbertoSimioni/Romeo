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
class ProtocolsExplorer : public QWidget
{
    Q_OBJECT

public:
    explicit ProtocolsExplorer(QWidget *parent = 0);
    ~ProtocolsExplorer();

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

private slots:

    void fillProtocolsExplorer();

private:
    Ui::ProtocolsExplorer *ui;

    romeo::model::protocols::ProtocolType currentProtocolsType;

    romeo::model::protocols::ProtocolsList* protocolsList;
};
}}}
#endif // PROTOCOLSEXPLORER_H
