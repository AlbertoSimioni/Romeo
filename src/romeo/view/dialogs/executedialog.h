/**
* \file executedialog.h
* \author Alessandro Strenghetto
* \date 2014-02-17
**
* \brief Header della classe ExecuteDialog del package romeo::view::dialogs
*/

#ifndef EXECUTEDIALOG_H
#define EXECUTEDIALOG_H

#include <QDialog>
namespace Ui {
class ExecuteDialog;
}

namespace romeo {
namespace view {
namespace dialogs {


class ExecuteDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ExecuteDialog(QWidget *parent = 0);
    ~ExecuteDialog();

private:
    Ui::ExecuteDialog *ui;
};
}}}


#endif // EXECUTEDIALOG_H
