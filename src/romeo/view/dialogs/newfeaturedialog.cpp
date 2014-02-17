#include "newfeaturedialog.h"
#include "ui_newfeaturedialog.h"
using namespace romeo::view::dialogs;
NewFeatureDialog::NewFeatureDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewFeatureDialog)
{
    ui->setupUi(this);
}

NewFeatureDialog::~NewFeatureDialog()
{
    delete ui;
}
