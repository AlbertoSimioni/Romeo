/**
* \file newfeaturedialog.h
* \author Alessandro Strenghetto
* \date 2014-02-17
**
* \brief Header della classe NewFeatureDialog del package romeo::view::dialogs
*/

#ifndef NEWFEATUREDIALOG_H
#define NEWFEATUREDIALOG_H

#include <QDialog>
namespace Ui {
class NewFeatureDialog;
}

namespace romeo{
namespace view{
namespace dialogs {

class NewFeatureDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NewFeatureDialog(QWidget *parent = 0);
    ~NewFeatureDialog();

private:
    Ui::NewFeatureDialog *ui;
};
}}}




#endif // NEWFEATUREDIALOG_H
