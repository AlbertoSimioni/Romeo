#include "aboutdialog.h"
#include "ui_aboutdialog.h"

using namespace romeo::view::dialogs;

AboutDialog::AboutDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutDialog)
{
    ui->setupUi(this);
}

AboutDialog::~AboutDialog()
{
    delete ui;
}
