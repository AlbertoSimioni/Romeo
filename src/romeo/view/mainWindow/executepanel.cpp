#include "executepanel.h"
#include "ui_executepanel.h"
#include <QFileDialog>

using namespace romeo::view::mainWindow;
ExecutePanel::ExecutePanel(QWidget *parent) :
    QWidget(parent), currentDataset(0),
    ui(new Ui::ExecutePanel)
{
    ui->setupUi(this);
    ui->resultLineEdit->setText("asd");
    connectUI();
    checkForm();
}

ExecutePanel::~ExecutePanel()
{
    delete ui;
}


void ExecutePanel::connectUI(){
    connect(ui->resultLineEdit,SIGNAL(textChanged(QString)),this,SLOT(checkForm()));
    connect(ui->browseButton,SIGNAL(clicked()),this,SLOT(onBrowseButtonClicked()));
    connect(ui->start,SIGNAL(clicked()),this,SLOT(onStartClicked()));
    connect(ui->viewResultsCheck,SIGNAL(clicked(bool)),this,SLOT(onViewResultsCliked(bool)));

}

void ExecutePanel::setCurrentDataset(romeo::model::datasets::AbstractDataset *dataset)
{
    currentDataset = dataset;
    checkForm();

}


void ExecutePanel::onBrowseButtonClicked(){
    QString dir = QFileDialog::getExistingDirectory(this, tr("Results Directory"),
                                                     "/home",
                                                     QFileDialog::ShowDirsOnly
                                                     | QFileDialog::DontResolveSymlinks);

    ui->resultLineEdit->setText(dir);
}

void ExecutePanel::checkForm(){
   QString path =  ui->resultLineEdit->text();
   if(QDir(path).exists() && (!path.isEmpty()) && (currentDataset != 0))
       ui->start->setEnabled(true);
   else
       ui->start->setEnabled(false);
}


void ExecutePanel::onStartClicked(){
    QString resultsPath = ui->resultLineEdit->text();
    bool viewResults = ui->viewResultsCheck->isChecked();
    bool viewFeatures = ui->viewFeaturesCheck->isChecked();
    bool saveFeatures = ui->saveFeaturesCheck->isChecked();
    QString format = ui->formatCombo->currentText();
    emit executeAnalysis(resultsPath,viewResults,viewFeatures,saveFeatures,format);

}


void ExecutePanel::onViewResultsCliked(bool state){
    if(state){
        ui->viewFeaturesCheck->setEnabled(true);
    }
    else{
        ui->viewFeaturesCheck->setEnabled(false);
        ui->viewFeaturesCheck->setChecked(false);
    }

}
