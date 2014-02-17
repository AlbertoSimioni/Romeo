/**
* \file protocoldialog.h
* \author Alessandro Strenghetto
* \date 2014-02-17
**
* \brief Header della classe ProtocolDialog del package romeo::view::dialogs
*/

#ifndef PROTOCOLDIALOG_H
#define PROTOCOLDIALOG_H

#include <QDialog>
namespace Ui {
class ProtocolDialog;
}

namespace romeo{
namespace view{
namespace dialogs{


class ProtocolDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ProtocolDialog(QWidget *parent = 0);
    ~ProtocolDialog();

private:
    Ui::ProtocolDialog *ui;
};
}}}
#endif // PROTOCOLDIALOG_H
