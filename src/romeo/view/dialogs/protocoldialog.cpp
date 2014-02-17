#include "protocoldialog.h"
#include "ui_protocoldialog.h"
using namespace romeo::view::dialogs;
ProtocolDialog::ProtocolDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ProtocolDialog)
{
    ui->setupUi(this);
}

ProtocolDialog::~ProtocolDialog()
{
    delete ui;
}
