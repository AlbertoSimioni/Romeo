/**
* \file protocoldialog.h
* \author Alessandro Strenghetto
* \date 2014-02-17
**
* \brief Header della classe ProtocolDialog del package romeo::view::dialogs
*/

#ifndef PROTOCOLDIALOG_H
#define PROTOCOLDIALOG_H

#include <QDialog>
namespace Ui {
class ProtocolDialog;
}

namespace romeo{
namespace view{
namespace dialogs{


class ProtocolDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ProtocolDialog(QWidget *parent = 0);
    ~ProtocolDialog();
    /*!
     * \brief Se il flag é true viene mostrato un messaggio di errore per avvertire l'utente che il nome del protocollo inserito è già utilizzato,
     * se il flag é false nasconde il messaggio
     */
    void showErrorName(bool flag);
    /*!
     * \brief Fa avanzare il wizard al prossimo passo, se è invocato all'ultimo passo, non fa nulla
     */
    void nextStep();

signals:
    void checkName(QString protocolName);


private:
    Ui::ProtocolDialog *ui;
};
}}}
#endif // PROTOCOLDIALOG_H
