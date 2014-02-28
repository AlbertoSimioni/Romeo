/**
* \file addsubjectdialog.h
* \author Alessandro Strenghetto
* \date 2014-02-17
**
* \brief Header della classe AddSubjectDialog del package romeo::view::dialogs
*/

#ifndef ADDSUBJECTDIALOG_H
#define ADDSUBJECTDIALOG_H

#include <QDialog>
#include <src/romeo/model/datasets/abstractdataset.h>
namespace Ui {
class AddSubjectDialog;
}

namespace romeo {
namespace view {
namespace dialogs {
// DA SISTEMARE LA PRESSIONE DELL'OK E IL SEGNALE PER CONTROLLARE LA VALIDITà DEL NOME E IL FILTRO PER L'INPUT
class AddSubjectDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddSubjectDialog(QWidget *parent = 0);
    ~AddSubjectDialog();


    /*!
     * \brief Se il flag é true viene mostrato un messaggio di errore per avvertire l'utente che il nome del subject inserito è già utilizzato,
     * se il flag é false nasconde il messaggio
     */
    void showErrorName(bool show);
    /*!
     * \brief Ritorna il riferimento al dataset corrente
     */
    romeo::model::datasets::AbstractDataset *getCurrentDataset() const;
    /*!
     * \brief Cambia il riferimento al dataset corrente
     */
    void setCurrentDataset(romeo::model::datasets::AbstractDataset *dataset);

public slots:
    /*!
     * \brief Override del metodo reject() della classe QDialog, il metodo deve azzerare le varie form del dialogo
     * e poi invocare il metodo reject() della classe QDialog per effettuare la chiusare del dialogo
     */
    virtual void reject();



signals:

    /*!
     * \brief Segnala la modifica del nome del subject da parte dell'utente
     */
    void nameChanged(QString datasetName);
private slots:

    /*!
     * \brief Slot avviato al cambiamento della linee di testo nella form
     *
     * Verifica che la linee di testo per l'inserimento del nome del subject e del percorso all'immagine non siano vuoti. Se non sono vuoti abilita la pressione del pulsante "ok", altrimenti la disabilita
     */
    void checkForm();

private:
    /*!
     * \brief Effettua le connessioni dei segnali inviati dai vari widget che compongono la classe NewSubjectDialog
     */
    void connectUI();


    /*!
     * \brief Svuota tutte le form del dialogo che l'utente ha modificato
     */
    void resetForms();


    romeo::model::datasets::AbstractDataset * currentDataset;




private:
    Ui::AddSubjectDialog *ui;
};

}

}

}


#endif // ADDSUBJECTDIALOG_H
