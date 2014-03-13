/**
* \file featureslistdialog.h
* \author Alessandro Strenghetto
* \date 2014-02-17
**
* \brief Header della classe FeaturesListDialog del package romeo::view::dialogs
*/


#ifndef FEATURESLISTDIALOG_H
#define FEATURESLISTDIALOG_H

#include <QDialog>
#include <src/romeo/model/protocols/features/featureslist.h>
namespace Ui {
class FeaturesListDialog;
}

namespace romeo {
namespace view {
namespace dialogs {

/*!
 * \brief Consente all'utente di visualizzare la lista di tutte le feature e la relativa descrizione.	Mostra una finestra di dialogo, separata da quella principale, che visualizza la lista delle feature.
 *
 * Selezionando una feature verrà mostrata la realtiva descrizione.
 */
class FeaturesListDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FeaturesListDialog(romeo::model::protocols::features::FeaturesList *feats, QWidget *parent = 0);
    ~FeaturesListDialog();
private slots:

    /*!
     * \brief Riempie o aggiorna la lista delle feature con le feature presenti nel modello
     */
    void fillFeaturesList();
    /*!
     * \brief Slot avviato alla sezione da parte dell'utente di una feature.
     *
     * Si preoccupa di mostrare nell'apposito riquadro di testo la descrizione della feature selezionata
     */
    void showDescription();

private:
    /*!
     * \brief Riferimento alla lista delle feature
     */
    romeo::model::protocols::features::FeaturesList * features;

    /*!
     * \brief Effettua le connessioni dei segnali inviati dai vari widget che compongono la classe FeaturesDialog
     */
    void connectUI();

    Ui::FeaturesListDialog *ui;
};
}}}
#endif // FEATURESLISTDIALOG_H
