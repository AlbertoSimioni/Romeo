#ifndef NEWFEATUREDIALOG_H
#define NEWFEATUREDIALOG_H

#include <QDialog>

namespace Ui {
class NewFeatureDialog;
}

class NewFeatureDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NewFeatureDialog(QWidget *parent = 0);
    ~NewFeatureDialog();

private:
    Ui::NewFeatureDialog *ui;
};

#endif // NEWFEATUREDIALOG_H
