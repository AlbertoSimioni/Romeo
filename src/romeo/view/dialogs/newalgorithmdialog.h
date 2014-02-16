#ifndef NEWALGORITHMDIALOG_H
#define NEWALGORITHMDIALOG_H

#include <QDialog>

namespace Ui {
class NewAlgorithmDialog;
}

class NewAlgorithmDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NewAlgorithmDialog(QWidget *parent = 0);
    ~NewAlgorithmDialog();

private:
    Ui::NewAlgorithmDialog *ui;
};

#endif // NEWALGORITHMDIALOG_H
