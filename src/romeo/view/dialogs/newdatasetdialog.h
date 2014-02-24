/**
* \file newdatasetdialog.h
* \author Alessandro Strenghetto
* \date 2014-02-17
**
* \brief Header della classe NewDatasetDialog del package romeo::view::dialogs
*/

#ifndef NEWDATASETDIALOG_H
#define NEWDATASETDIALOG_H

#include <QDialog>

namespace Ui {
class NewDatasetDialog;
}

namespace romeo{
namespace view {
namespace dialogs{

//MANCA PULSANTE OK
class NewDatasetDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NewDatasetDialog(QWidget *parent = 0);
    ~NewDatasetDialog();

    /*!
     * \brief Se il flag é true viene mostrato un messaggio di errore per avvertire l'utente che il nome del daset inserito è già utilizzato,
     * se il flag é false nasconde il messaggio
     */
    void showErrorName(bool show);

public slots:
    /*!
     * \brief Override del metodo reject() della classe QDialog, il metodo deve azzerare le varie form del dialogo
     * e poi invocare il metodo reject() della classe QDialog per effettuare la chiusare del dialogo
     */
    virtual void reject();



signals:

    /*!
     * \brief Segnala la modifica del nome della feature da parte dell'utente
     */
    void nameChanged(QString datasetName);
private slots:

    /*!
     * \brief Slot avviato al cambiamento della linee di testo nella form
     *
     * Verifica che la linea di testo contenente il nome del dataset non sia vuota. Se non vuota abilita la pressione del pulsante "ok", altrimento la disabilita
     */
    void checkForm();

private:
    /*!
     * \brief Effettua le connessioni dei segnali inviati dai vari widget che compongono la classe NewDatasetDialog
     */
    void connectUI();


    /*!
     * \brief Svuota tutte le form del dialogo che l'utente ha modificato
     */
    void resetForms();
    Ui::NewDatasetDialog *ui;
};
}}}
#endif // NEWDATASETDIALOG_H
