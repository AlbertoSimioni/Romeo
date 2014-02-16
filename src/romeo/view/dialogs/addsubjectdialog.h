#ifndef ADDSUBJECTDIALOG_H
#define ADDSUBJECTDIALOG_H

#include <QDialog>

namespace Ui {
class AddSubjectDialog;
}

class AddSubjectDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddSubjectDialog(QWidget *parent = 0);
    ~AddSubjectDialog();

private:
    Ui::AddSubjectDialog *ui;
};

#endif // ADDSUBJECTDIALOG_H
