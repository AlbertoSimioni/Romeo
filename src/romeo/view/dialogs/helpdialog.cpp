#include "helpdialog.h"
#include "ui_helpdialog.h"
#include<QTextBrowser>
#include<QWebPage>
#include<QToolBar>
using namespace romeo::view::dialogs;
HelpDialog::HelpDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::HelpDialog)
{
    ui->setupUi(this);
    //helpView=new QWebView(ui->scrollArea);
    QFile file(":/doc/doc/help.html");
    if(!file.open(QIODevice::ReadOnly))
        return;
    QString content();
    //helpView->setContent(file.readAll());


    QTextBrowser* br=new QTextBrowser(this);
    br->setHtml(QString(file.readAll()));
    br->setOpenLinks(true);
    //helpView->page()->setLinkDelegationPolicy(QWebPage::DelegateAllLinks);
    this->resize(700, 500);
    ui->scrollArea->setWidget(br);
    file.close();
}

HelpDialog::~HelpDialog()
{
    delete ui;
}


