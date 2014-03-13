/**
* \file newfeaturedialog.h
* \author Alessandro Strenghetto
* \date 2014-02-17
**
* \brief Header della classe NewFeatureDialog del package romeo::view::dialogs
*/

#ifndef NEWFEATUREDIALOG_H
#define NEWFEATUREDIALOG_H
#include <src/romeo/model/protocols/features/abstractfeature.h>
#include <QDialog>
namespace Ui {
class NewFeatureDialog;
}

namespace romeo{
namespace view{
namespace dialogs {

/*!
 * \brief Fornisce all'utente una finestra per inserire le informazioni relative alla feature da inserire, come il percorso del file associato, il nome e la lista dei parametri.
 *
 * Permette di mostrare una finestra di dialogo quando l'utente richiede di aggiungere una feature al programma e di restituire le informazioni inserite dall'utente.
 */
class NewFeatureDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NewFeatureDialog(QWidget *parent = 0);
    ~NewFeatureDialog();
    /*!
     * \brief Se il flag é true viene mostrato un messaggio di errore per avvertire l'utente che il nome della feature inserita è già utilizzata,
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
    void nameChanged(QString featureName);

    /*!
     * \brief Segnale emesso per avvertire la creazione da parte dell'utente di un nuovo feature extractor, contiene tutti i parametri inseriti dall'utente
     */
    void createFeature(QString name,QString desc, QString dyfn, QString dylp,romeo::model::protocols::features::FeatureType type);

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
     * \brief Slot avviato alla pressione dell'utente del tasto ok
     */
    void okButtonClicked();

private:
    /*!
     * \brief Effettua le connessioni dei segnali inviati dai vari widget che compongono la classe NewFeatureDialog
     */
    void connectUI();

    /*!
     * \brief Svuota tutte le form del dialogo che l'utente ha modificato
     */
    void resetForms();

    Ui::NewFeatureDialog *ui;
};
}}}




#endif // NEWFEATUREDIALOG_H
