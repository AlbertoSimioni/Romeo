#ifndef HELPDIALOG_H
#define HELPDIALOG_H

#include <QScrollArea>
#include <QtWebKitWidgets/QtWebKitWidgets>

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


private slots:
    void changeView(QUrl);

private:
    QWebView* helpView;
    Ui::HelpDialog *ui;



    QTextBrowser* textBrowser;
};

}}}

#endif // HELPDIALOG_H
