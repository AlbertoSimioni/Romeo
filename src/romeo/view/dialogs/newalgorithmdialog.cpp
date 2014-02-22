#include "newalgorithmdialog.h"
#include "ui_newalgorithmdialog.h"
#include <QFileDialog>
#include <QDir>

using namespace romeo::view::dialogs;

NewAlgorithmDialog::NewAlgorithmDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewAlgorithmDialog)
{
    ui->setupUi(this);
    connectUI();
}

void NewAlgorithmDialog::connectUI(){
    connect(ui->browseButton,SIGNAL(clicked()),this,SLOT(openBrowseDialog()));
}

NewAlgorithmDialog::~NewAlgorithmDialog()
{
    delete ui;
}


void NewAlgorithmDialog::openBrowseDialog(){
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Select dynamic library"), QDir::home().path(), tr("Dynamic library files (*.so *.dll *.dylib)"));
    if(!fileName.isNull())
        ui->pathLineEdit->setText(fileName);
}
