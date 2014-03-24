#ifndef HELPDIALOG_H
#define HELPDIALOG_H

#include <QScrollArea>

namespace Ui {
class HelpDialog;
}

class HelpDialog : public QScrollArea
{
    Q_OBJECT

public:
    explicit HelpDialog(QWidget *parent = 0);
    ~HelpDialog();

private:
    Ui::HelpDialog *ui;
};

#endif // HELPDIALOG_H
