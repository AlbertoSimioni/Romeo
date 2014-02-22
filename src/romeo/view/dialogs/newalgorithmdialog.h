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
private slots:
    /*!
     * \brief Apre la finestra di dialogo per selezionare la libreria dinamica.
     *
     * Il dialogo deve mostrare solamente le estensioni .os .dll e .lib e deve inserire il percorso nella linea di testo associata al percorso nel file system
     */
    void openBrowseDialog();

signals:
    /*!
     * \brief Segnala la modifica del nome dell'algoritmo da parte dell'utente
     */
    void nameChanged(QString algorithmName);

private:
    /*!
     * \brief Effettua le connessioni dei segnali inviati dai vari widget che compongono la classe NewAlgorithmDialog
     */
    void connectUI();

    /*!
     * \brief Svuota tutte le form del dialogo che l'utente ha modificato
     */
    void resetForms();



    Ui::NewAlgorithmDialog *ui;
};
}}}




#endif // NEWALGORITHMDIALOG_H
