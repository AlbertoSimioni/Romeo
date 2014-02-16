#include "addsubjectdialog.h"
#include "ui_addsubjectdialog.h"

AddSubjectDialog::AddSubjectDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddSubjectDialog)
{
    ui->setupUi(this);
}

AddSubjectDialog::~AddSubjectDialog()
{
    delete ui;
}
