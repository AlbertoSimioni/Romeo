/**
* \file executepanel.cpp
* \author Alessandro Strenghetto
* \date 2014-02-17
**
* \brief Header della classe ExecutePanel del package romeo::view::mainWindow
*/

#include "executepanel.h"
#include "ui_executepanel.h"
#include <QFileDialog>
#include <QSettings>

using namespace romeo::view::mainWindow;
using namespace romeo::model;
ExecutePanel::ExecutePanel(QWidget *parent) :
    QWidget(parent), currentDataset(0),
    ui(new Ui::ExecutePanel)
{

    ui->setupUi(this);
    connectUI();
    QSettings settings;
    ui->resultLineEdit->setText(settings.value("res").toString());
    ui->label_4->setHidden(true);
    checkForm();
}

ExecutePanel::~ExecutePanel()
{
    QSettings settings;
    settings.setValue("res",ui->resultLineEdit->text());
    delete ui;
}


void ExecutePanel::connectUI(){
    connect(ui->resultLineEdit,SIGNAL(textChanged(QString)),this,SLOT(checkForm()));
    connect(ui->browseButton,SIGNAL(clicked()),this,SLOT(onBrowseButtonClicked()));
    connect(ui->start,SIGNAL(clicked()),this,SLOT(onStartClicked()));
    connect(ui->viewResultsCheck,SIGNAL(clicked(bool)),this,SLOT(onViewResultsCliked(bool)));
    connect(ui->saveFeaturesCheck,SIGNAL(clicked(bool)),this,SLOT(onViewResultsCliked(bool)));

}

void ExecutePanel::setCurrentDataset(romeo::model::datasets::AbstractDataset *dataset)
{
    if(currentDataset){
        if(currentDataset->getType() == TYPE3D || currentDataset->getType() == TYPE3DT)
            disconnect(ui->viewFeaturesCheck,SIGNAL(clicked(bool)),ui->label_4,SLOT(setVisible(bool)));
    }
    currentDataset = dataset;
    ui->formatCombo->clear();
    if(currentDataset){

        if(currentDataset->getType() == TYPE3D || currentDataset->getType() == TYPE3DT){
            connect(ui->viewFeaturesCheck,SIGNAL(clicked(bool)),ui->label_4,SLOT(setVisible(bool)));
            ui->label_4->setVisible(ui->viewFeaturesCheck->isChecked());
        }
        else ui->label_4->setHidden(true);
        QStringList formats;
        switch(currentDataset->getType()){
        case TYPE2D : formats << "INPUT" <<".jpg" << ".png" << ".tif" << ".bmp";
            break;
        case TYPE3D : formats << "INPUT"<< ".nii" << ".hdr";
            break;
        case TYPE2DT : formats <<".jpg" << ".png" << ".tif" << ".bmp";
            break;
        case TYPE3DT: formats << "INPUT" << ".nii" << ".hdr";
            break;
        }
        ui->formatCombo->addItems(formats);
    }
    else ui->label_4->setHidden(true);
    checkForm();

}


void ExecutePanel::onBrowseButtonClicked(){
    QSettings settings;
    QString resultsPath = settings.value("resultsPath").toString();

    QString dir = QFileDialog::getExistingDirectory(this, tr("Results Directory"),
                                                     resultsPath,
                                                     QFileDialog::ShowDirsOnly
                                                     | QFileDialog::DontResolveSymlinks);


    settings.setValue("resultsPath",dir);
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
    if(ui->viewResultsCheck->isChecked() && ui->saveFeaturesCheck->isChecked()){
        ui->viewFeaturesCheck->setEnabled(true);
    }
    else{
        ui->viewFeaturesCheck->setEnabled(false);
        ui->viewFeaturesCheck->setChecked(false);
    }

}
