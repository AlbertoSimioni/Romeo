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


namespace Ui {
class ProtocolDialog;
}

namespace romeo{
namespace view{
namespace dialogs{

//DA SISTEMARE TUTTA LA ROBA DELLE FEATURE E DEGLI ALGORITMI E DEI PARAMETRI
class ProtocolDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ProtocolDialog(
            //romeo::model::protocols::algorithms::AlgorithmsList* al,
            //romeo::model::protocols::features::FeaturesList* fl,
            QWidget *parent = 0);

    ~ProtocolDialog();
    /*!
     * \brief Se il flag é true viene mostrato un messaggio di errore per avvertire l'utente che il nome del protocollo inserito è già utilizzato,
     * se il flag é false nasconde il messaggio
     */
    void showErrorName(bool show);

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


    /*!
     * \brief Svuota tutte le form del dialogo che l'utente ha modificato
     */
    void resetForms();


    /*!
     * \brief Effettua le connessioni dei segnali inviati dai vari widget che compongono la classe ProtocolDialog
     */
    void connectUI();



private slots:
    /*!
     * \brief Aggiunge l'item dato in input alla lista delle feature del protocollo
     */

    void addFeature(QListWidgetItem* item);
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
};
}}}
#endif // PROTOCOLDIALOG_H
