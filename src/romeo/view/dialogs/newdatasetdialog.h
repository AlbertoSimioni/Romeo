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


class NewDatasetDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NewDatasetDialog(QWidget *parent = 0);
    ~NewDatasetDialog();
    /*!
     * \brief Mostra un messaggio di errore per avvertire l'utente che il nome del dataset inserito è già utilizzato.
     */
    void showErrorName();

private:
    Ui::NewDatasetDialog *ui;
};
}}}
#endif // NEWDATASETDIALOG_H
