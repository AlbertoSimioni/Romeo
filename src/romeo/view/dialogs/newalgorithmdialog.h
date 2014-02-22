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
private slots:
    /*!
     * \brief Apre la finestra di dialogo per selezionare la libreria dinamica.
     *
     * Il dialogo deve mostrare solamente le estensioni .os .dll e .lib e deve inserire il percorso nella linea di testo associata al percorso nel file system
     */
    void openBrowseDialog();

private:
    /*!
     * \brief Effettua le connessioni dei segnali inviati dai vari widget che compongono la classe NewAlgorithmDialog
     */
    void connectUI();



    Ui::NewAlgorithmDialog *ui;
};
}}}




#endif // NEWALGORITHMDIALOG_H
