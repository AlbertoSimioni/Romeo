#include "executedialog.h"
#include "ui_executedialog.h"
#include <QCloseEvent>
using namespace romeo::view::dialogs;
ExecuteDialog::ExecuteDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ExecuteDialog)
{
    ui->setupUi(this);
    connect(ui->cancelButton,SIGNAL(clicked()),this,SLOT(reject()));
}

ExecuteDialog::~ExecuteDialog()
{
    delete ui;
}

void ExecuteDialog::closeEvent(QCloseEvent *event) {

//event->ignore(); // keep window

}
