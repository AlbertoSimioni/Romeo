/**
* \file addsubjectdialog.h
* \author Alessandro Strenghetto
* \date 2014-02-17
**
* \brief Header della classe AddSubjectDialog del package romeo::view::dialogs
*/

#ifndef ADDSUBJECTDIALOG_H
#define ADDSUBJECTDIALOG_H

#include <QDialog>

namespace Ui {
class AddSubjectDialog;
}

namespace romeo {
namespace view {
namespace dialogs {

class AddSubjectDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddSubjectDialog(QWidget *parent = 0);
    ~AddSubjectDialog();

private:
    Ui::AddSubjectDialog *ui;
};

}

}

}


#endif // ADDSUBJECTDIALOG_H
