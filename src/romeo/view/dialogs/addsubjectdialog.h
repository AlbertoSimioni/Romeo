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
#include <src/romeo/model/inputformats.h>
namespace Ui {
class AddSubjectDialog;
}

namespace romeo {
namespace view {
namespace dialogs {
// TODO DA SISTEMARE LA PRESSIONE DELL'OK E IL SEGNALE PER CONTROLLARE LA VALIDITà DEL NOME E IL FILTRO PER L'INPUT

/*!
 * \brief Mostra una finestra all'utente da cui può aggiungere un subject selezionando l'immagine corrispondente al suo data e l'eventuale maschera dal file system.
 *
 * Fornisce le informazioni sulle scelte dell'utente e notifica all'utente l'eventuale errato inserimento di immagini che non sono valide o corrispondenti al formato selezionato. Notifica inoltre l'eventuale errato inserimento di una maschera in caso essa abbia una dimensione non conforme a quella dell'immagine inserita per il campo data del subject.
 */
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
     * \brief Cambia il formato corrente dei dati in input
     */
    void setCurrentInputFormat(const romeo::model::InputFormat &value);

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
    void nameChanged(QString subjectName);

    /*!
     * \brief Segnale emesso quando l'utente ha terminato le operazioni necessarie per la creazione di un nuovo subject
     * \param name
     * \param data
     * \param mask
     */
    void createNewSubject(QString name, QString data, QString mask);
private slots:

    /*!
     * \brief Slot avviato al cambiamento della linee di testo nella form
     *
     * Verifica che la linee di testo per l'inserimento del nome del subject e del percorso all'immagine non siano vuoti. Se non sono vuoti abilita la pressione del pulsante "ok", altrimenti la disabilita
     */
    void checkForm();

    /*!
     * \brief Apre la finestra di dialogo per selezionare l'immagine del campo data del subject
     *
     * Il dialogo deve mostrare solamente le estensioni dei file coerenti col tipo di dataset corrente
     */
    void openBrowseDataDialog();


    /*!
     * \brief Apre la finestra di dialogo per selezionare l'immagine corrispondente alla maschera del subject
     *
     * Il dialogo deve mostrare solamente le estensioni dei file coerenti col tipo di dataset corrente
     */
    void openBrowseMaskDialog();

    /*!
     * \brief Slot avviato alla pressione dell'utente del tasto ok
     */
    void okButtonClicked();

private:
    /*!
     * \brief Effettua le connessioni dei segnali inviati dai vari widget che compongono la classe NewSubjectDialog
     */
    void connectUI();


    /*!
     * \brief Svuota tutte le form del dialogo che l'utente ha modificato
     */
    void resetForms();

    /*!
     * \brief Cambia i filtri sulle estensioni dei file da visualizzare in base al formato di input corrente
     */
    void changeFilters();
    /*!
     * \brief Tipo delle immagini che possono essere associate al dataset correntemente visualizzato
     */
    romeo::model::InputFormat currentInputFormat;

    QString currentFilters;

    Ui::AddSubjectDialog *ui;
};

}

}

}


#endif // ADDSUBJECTDIALOG_H
