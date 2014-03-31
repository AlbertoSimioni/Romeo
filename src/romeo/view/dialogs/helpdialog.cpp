#include "helpdialog.h"
#include "ui_helpdialog.h"
#include<QTextBrowser>
#include<QToolBar>
#include <QDebug>
using namespace romeo::view::dialogs;
HelpDialog::HelpDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::HelpDialog)
{
    ui->setupUi(this);
    QFile file(":/doc/doc/help.html");
    if(!file.open(QIODevice::ReadOnly))
        return;
    this->setFixedSize(900, 610);
    textBrowser=new QTextBrowser(this);
    textBrowser->setHtml(QString(file.readAll()));
    textBrowser->setOpenLinks(true);
    connect(textBrowser,SIGNAL(anchorClicked(QUrl)),this,SLOT(changeView(QUrl)));

    ui->scrollArea->setWidget(textBrowser);

    file.close();
}

HelpDialog::~HelpDialog()
{
    delete ui;
}


void HelpDialog::changeView(QUrl link){
    QString fileName = link.toString();
    if(!(fileName.at(0) == '#'))
        fileName = ":"+fileName;


    QFile file(fileName);
    if(!file.open(QIODevice::ReadOnly))
        return;
    textBrowser->setHtml(QString(file.readAll()));
}
