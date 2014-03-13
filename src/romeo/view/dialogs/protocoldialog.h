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
#include <QListWidgetItem>
#include <QVector>
#include <src/romeo/model/protocols/algorithms/abstractalgorithm.h>
#include <src/romeo/view/dialogs/parametervalueform.h>
#include <src/romeo/model/protocols/algorithms/algorithmslist.h>
#include <src/romeo/model/protocols/features/featureslist.h>
#include <src/romeo/model/protocols/abstractprotocol.h>
#include "src/romeo/model/protocols/abstractprotocol.h"


namespace Ui {
class ProtocolDialog;
}

namespace romeo{
namespace view{
namespace dialogs{


/*!
 * \brief Fornisce all'utente una finestra in cui può creare un nuovo protocollo inserendo la lista di feature da estrarre e l'eventuale algoritmo di clustering tra quelli disponibili con i rispettivi parametri da utilizzare.
 *
 * La classe fornisce metodi per reperire le informazioni inserite dall'utente riguardanti il protocollo creato, o se la creazione del protocollo è stata annullata.
 */
class ProtocolDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ProtocolDialog(
            romeo::model::protocols::algorithms::AlgorithmsList* al,
            romeo::model::protocols::features::FeaturesList* fl,
            QWidget *parent = 0);

    ~ProtocolDialog();

    /*!
     * \brief Se il flag é true viene mostrato un messaggio di errore per avvertire l'utente che il nome del protocollo inserito è già utilizzato,
     * se il flag é false nasconde il messaggio
     */
    void showErrorName(bool show);

    /*!   !!!!
     * \brief Meotodo per la visualizzazione di un protocollo già esistente, in caso sia di test permette anche la modifica
     *
     */
    void openExistingProtocol(romeo::model::protocols::AbstractProtocol* protocol);
public slots:
    /*!
     * \brief Fa avanzare il wizard al prossimo passo, se è invocato mentre il wizard è all'ultimo passo del wizard non fa nulla
     */
    void nextStep();

    /*!
     * \brief Fa tornare indietro il wizard al passo precedente, se invocato mentre il wizard è al primo passo non fa nulla
     */
    void previousStep();

    /*!
     * \brief Override del metodo reject() della classe QDialog, il metodo deve azzerare le varie form del dialogo
     * e poi invocare il metodo reject() della classe QDialog per effettuare la chiusare del dialogo
     */
    virtual void reject();

signals:
    /*!
     * \brief Segnala la modifica del nome del protocollo da parte dell'utente
     */
    void nameChanged(QString protocolName);

    /*!
     * \brief Segnala la creazione di un nuovo protocollo da parte dell'utente, il segnale contiene tutti i campi dati necessari per la creazione del protocollo
     * \param protocolName Nome del protocollo
     * \param desc Descrizione del protocollo
     * \param test Booleano che segnala se il protocollo è di test oppure no
     * \param features Elenco delle features associate
     * \param algorithm Algoritmo associato
     * \param type Tipo del protocollo
     */
    void createProtocol(QString protocolName,QString desc,bool test,QList<QString>features,QString algorithm,romeo::model::protocols::ProtocolType type,int windowSize,int distanceGLCM,int nClusters,QList<QString> parametersValue);

    /*!
     * \brief Segnala la volontà dell'utente di moficare un protocollo
     * \param oldProtocolName
     * \param protocolName
     * \param desc
     * \param test
     * \param features
     * \param algorithm
     * \param type
     * \param windowSize
     * \param distanceGLCM
     * \param nClusters
     * \param parametersValue
     */
    void modifyProtocol(QString oldProtocolName,QString protocolName,QString desc,bool test,QList<QString>features,QString algorithm,romeo::model::protocols::ProtocolType type,int windowSize,int distanceGLCM,int nClusters,QList<QString> parametersValue);


private:
    Ui::ProtocolDialog *ui;

    /*!
     * \brief Contiene i riferimenti ai widget per l'inserimento dei parametri dell'algoritmo
     */
    QVector<ParameterValueForm*> parameters;

    /*!
     * \brief Riferimento alla lista degli algoritmi
     */
    romeo::model::protocols::algorithms::AlgorithmsList* algorithmsList;

    /*!
     * \brief Riferimento alla lista delle feature
     */
    romeo::model::protocols::features::FeaturesList* featuresList;

    /*!  !!!!
     * \brief campo dati contenente il nome di origine del protocollo di test che l'utente sta modificando
     */
    QString oldProtocol;

    /*!
     * \brief Campo dati che indica se il protocollo di origine è di test
     */
    bool oldProtocolTest;


    /*!
     * \brief Svuota tutte le form del dialogo che l'utente ha modificato
     */
    void resetForms();


    /*!
     * \brief Effettua le connessioni dei segnali inviati dai vari widget che compongono la classe ProtocolDialog
     */
    void connectUI();

    /*! !!!
     * \brief Disabilita/abilita la modifica di tutti i widget che permettono il cambiamento dei dati del protocollo
     */
    void setAllDisabled(bool disable );





private slots:
    /*! !!!
     * \brief Slot che controlla se il nome del protocollo è diverso dal nome originale del protocollo che si sta modificando e in caso invia il segnale nameChanged
     */
    void onProtocolNameChanged();

    /*!
     * \brief Aggiunge l'item dato in input alla lista delle feature del protocollo
     */

    void addFeature(QListWidgetItem* item);

    /*!
     * \brief Metodo che inserisce nella lista delle feature, tutte le feature presenti nel modello
     */
    void fillFeaturesList();

    /*!
     * \brief Metodo che inserisce nella combo box la lista di tutti gli algoritmi di clustering
     */
    void fillAlgorithmsCombo();

    /*!
     * \brief Rimuove l'item dato in input dalla lista delle feature del protocollo
     */
    void removeFeature(QListWidgetItem* item);


    /*!
     * \brief Slot che inserisce nella lista delle feature del protocollo, la feature correntemente selezionata nella lista delle feature.
     * Se nessuna feature è selezionata non aggiunge nulla
     */
    void addButtonClicked();
    /*!
     * \brief Slot che elimina dalla lista delle feature del protocollo, la feature correntemente selezionata nella lista delle feature.
     * Se nessuna feature è selezionata non elimina nulla
     */
    void removeButtonClicked();

    /*!
     * \brief Slot che rimpiazza la form con i parametri dell'algoritmo con i parametri dell'algoritmo selezionato nella combo box degli algoritmi
     */
    void changeParametersForm();

    /*!
     * \brief Slot che controlla che tutti i valori dei parametri siano validi, in caso positivo rende abilitato il pulsante finish, in caso contrario lo disabilita
     */
    void checkParametersValidity();

    /*!
     * \brief Slot che verifica se la stringa in input è vuoto e in caso disabilita il bottone di avanzamento del primo passo del wizard
     */
    void checkEmpty(QString name);
    /*!
     * \brief Slot avviato alla pressione dell'utente del tasto finish
     */
    void finishButtonClicked();
    /*!
     * \brief Slot che verifica la validità dei parametri riguardanti la window size e la distance to the glcm
     */
    void checkWindowSizeGLCM();

};
}}}
#endif // PROTOCOLDIALOG_H
