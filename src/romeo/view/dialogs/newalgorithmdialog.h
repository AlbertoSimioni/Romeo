/**
* \file addsubjectdialog.h
* \author Alessandro Strenghetto
* \date 2014-02-17
**
* \brief Header della classe NewAlgorithmDialog del package romeo::view::dialogs
*/

#ifndef NEWALGORITHMDIALOG_H
#define NEWALGORITHMDIALOG_H

#include <QDialog>
#include <QList>
#include "newalgorithmparameterform.h"

namespace Ui {
class NewAlgorithmDialog;
}

namespace romeo{
namespace view {
namespace dialogs{


class NewAlgorithmDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NewAlgorithmDialog(QWidget *parent = 0);
    ~NewAlgorithmDialog();

    /*!
     * \brief Se il flag é true viene mostrato un messaggio di errore per avvertire l'utente che il nome dell'algoritmo inserito è già utilizzato,
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
     * \brief Segnala la modifica del nome dell'algoritmo da parte dell'utente
     */
    void nameChanged(QString algorithmName);
    /*!
     * \brief Segnale emesso per avvertire la creazione da parte dell'utente di un nuovo algoritmo di clustering, contiene tutti i parametri inseriti dall'utente
     */
    void createAlgorithm(QString name,QString desc, QString dyfn, QString dylp,QList<romeo::model::protocols::algorithms::AbstractAlgorithm::AlgorithmParameter> parameters);
private slots:

    /*!
     * \brief Apre la finestra di dialogo per selezionare la libreria dinamica.
     *
     * Il dialogo deve mostrare solamente le estensioni .os .dll e .lib e deve inserire il percorso nella linea di testo associata al percorso nel file system
     */
    void openBrowseDialog();

    /*!
     * \brief Slot avviato al cambiamento delle linee di testo nella form
     *
     * Verifica che le varie linee di testo non siano vuote, se non lo sono abilita la pressione del pulsante "ok", altrimento la disabilita
     */
    void checkForm();

    /*!
     * \brief Slot avviato alla pressione del tasto di aggiunta di un parametro, si preoccupa di aggiungere un nuovo parametro alla form
     */
    void addButtonClicked();

    /*!
     * \brief Slot avviato alla pressione di uno dei tasti per la rimozione di un parametro di un algoritmo.
     */
    void deleteButtonClicked(NewAlgorithmParameterForm *param);

    /*!
     * \brief Slot avviato alla pressione dell'utente del tasto ok
     */
    void okButtonClicked();

private:

    /*!
     * \brief Effettua le connessioni dei segnali inviati dai vari widget che compongono la classe NewAlgorithmDialog
     */
    void connectUI();

    /*!
     * \brief Svuota tutte le form del dialogo che l'utente ha modificato
     */
    void resetForms();


    QList<NewAlgorithmParameterForm*> parameters;

    Ui::NewAlgorithmDialog *ui;
};
}}}




#endif // NEWALGORITHMDIALOG_H
