/**
* \file algorithmslistdialog.h
* \author Alessandro Strenghetto
* \date 2014-02-17
**
* \brief Header della classe AlgorithmsListDialog del package romeo::view::dialogs
*/

#ifndef ALGORITHMSLISTDIALOG_H
#define ALGORITHMSLISTDIALOG_H

#include <QDialog>
#include "src/romeo/model/protocols/algorithms/algorithmslist.h"
namespace Ui {
class AlgorithmsListDialog;
}

namespace romeo {
namespace view {
namespace dialogs {


class AlgorithmsListDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AlgorithmsListDialog(
            romeo::model::protocols::algorithms::AlgorithmsList* al,
            QWidget *parent = 0);
    ~AlgorithmsListDialog();

private slots:

    /*!
     * \brief Riempie la lista degli algoritmi con gli algoritmi presenti nel modello
     */
    void fillAlgorithmsList();
    /*!
     * \brief Slot avviato alla sezione da parte dell'utente di un algoritmo.
     *
     * Si preoccupa di mostrare nell'apposito riquadro di testo la descrizione dell'algoritmo selezionato
     */
    void showDescription();

private:
    /*!
     * \brief Riferimento alla lista degli algoritmi
     */
    romeo::model::protocols::algorithms::AlgorithmsList * algorithms;

    /*!
     * \brief Effettua le connessioni dei segnali inviati dai vari widget che compongono la classe AlgorithmsDialog
     */
    void connectUI();
    Ui::AlgorithmsListDialog *ui;
};
}}}
#endif // ALGORITHMSLISTDIALOG_H
