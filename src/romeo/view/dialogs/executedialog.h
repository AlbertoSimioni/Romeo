#ifndef EXECUTEDIALOG_H
#define EXECUTEDIALOG_H

#include <QDialog>

namespace Ui {
class ExecuteDialog;
}

class ExecuteDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ExecuteDialog(QWidget *parent = 0);
    ~ExecuteDialog();

private:
    Ui::ExecuteDialog *ui;
};

#endif // EXECUTEDIALOG_H
