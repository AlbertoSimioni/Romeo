#include "executedialog.h"
#include "ui_executedialog.h"
using namespace romeo::view::dialogs;
ExecuteDialog::ExecuteDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ExecuteDialog)
{
    ui->setupUi(this);
}

ExecuteDialog::~ExecuteDialog()
{
    delete ui;
}
