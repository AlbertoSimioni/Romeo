#ifndef HELPDIALOG_H
#define HELPDIALOG_H

#include <QScrollArea>
#include <QtWebKitWidgets>

namespace Ui {
class HelpDialog;
}

namespace romeo {
namespace view {
namespace dialogs{

class HelpDialog : public QDialog
{
    Q_OBJECT

public:
    explicit HelpDialog(QWidget *parent = 0);
    ~HelpDialog();


private:
    QWebView* helpView;
    Ui::HelpDialog *ui;
};

}}}

#endif // HELPDIALOG_H
