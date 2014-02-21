#include "algorithmslistdialog.h"
#include "ui_algorithmslistdialog.h"
using namespace romeo::view::dialogs;
AlgorithmsListDialog::AlgorithmsListDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AlgorithmsListDialog)
{
    ui->setupUi(this);
}

AlgorithmsListDialog::~AlgorithmsListDialog()
{
    delete ui;
}
