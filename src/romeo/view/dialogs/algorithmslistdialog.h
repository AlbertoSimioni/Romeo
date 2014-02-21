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
    explicit AlgorithmsListDialog(QWidget *parent = 0);
    ~AlgorithmsListDialog();

private:
    Ui::AlgorithmsListDialog *ui;
};
}}}
#endif // ALGORITHMSLISTDIALOG_H
