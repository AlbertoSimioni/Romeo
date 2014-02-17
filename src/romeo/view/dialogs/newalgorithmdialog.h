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

private:
    Ui::NewAlgorithmDialog *ui;
};
}}}




#endif // NEWALGORITHMDIALOG_H
