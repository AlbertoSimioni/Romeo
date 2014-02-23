/**
* \file featureslistdialog.h
* \author Alessandro Strenghetto
* \date 2014-02-17
**
* \brief Header della classe FeaturesListDialog del package romeo::view::dialogs
*/


#ifndef FEATURESLISTDIALOG_H
#define FEATURESLISTDIALOG_H

#include <QDialog>

namespace Ui {
class FeaturesListDialog;
}

namespace romeo {
namespace view {
namespace dialogs {


class FeaturesListDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FeaturesListDialog(QWidget *parent = 0);
    ~FeaturesListDialog();

private:

    Ui::FeaturesListDialog *ui;
};
}}}
#endif // FEATURESLISTDIALOG_H
