#ifndef FEATURESLISTDIALOG_H
#define FEATURESLISTDIALOG_H

#include <QDialog>

namespace Ui {
class FeaturesListDialog;
}

class FeaturesListDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FeaturesListDialog(QWidget *parent = 0);
    ~FeaturesListDialog();

private:
    Ui::FeaturesListDialog *ui;
};

#endif // FEATURESLISTDIALOG_H
