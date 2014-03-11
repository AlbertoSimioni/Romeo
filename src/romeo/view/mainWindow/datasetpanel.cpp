#include "datasetpanel.h"
#include "ui_datasetpanel.h"

#include <QDebug>
#include <QFileInfo>
using namespace romeo::view::mainWindow;
using namespace romeo::model::datasets;
DatasetPanel::DatasetPanel(QWidget *parent) :
    QWidget(parent),currentDataset(0),
    ui(new Ui::DatasetPanel)
{
    ui->setupUi(this);
    connect(ui->executePanel,SIGNAL(executeAnalysis(QString,bool,bool,bool,QString)),this,SLOT(onExecuteclicked(QString,bool,bool,bool,QString)));

}

DatasetPanel::~DatasetPanel()
{
    delete ui;
}
romeo::model::datasets::AbstractDataset *DatasetPanel::getCurrentDataset() const
{
    return currentDataset;
}

void DatasetPanel::setCurrentDataset(romeo::model::datasets::AbstractDataset *dataset)
{
    currentDataset = dataset;
    if(currentDataset != 0){
        ui->datasetLabel->setText(currentDataset->getName());
    }
    else{
        ui->datasetLabel->setText("No Dataset");
    }
    ui->protocolsPanel->setCurrentDataset(currentDataset);
    ui->subjectsPanel->setCurrentDataset(currentDataset);
    ui->executePanel->setCurrentDataset(currentDataset);
}


ProtocolsPanel* DatasetPanel::getProtocolsPanel(){
    return ui->protocolsPanel;
}


SubjectsPanel* DatasetPanel::getSubjectsPanel(){
    return ui->subjectsPanel;
}


ExecutePanel* DatasetPanel::getExecutePanel(){
    return ui->executePanel;
}

void DatasetPanel::onExecuteclicked(QString resultsPath, bool viewResults, bool viewFeatures, bool saveFeatures, QString format){
   QString protocol = ui->protocolsPanel->getSelectedProtocol();
   QList<QString> subjects = ui->subjectsPanel->getCheckedSubjects();
   bool validSubjects = true;
   QString message = "Can't find the following files: \n";
   for(int i = 0; i < subjects.size();i++){
       QString pathData = currentDataset->getSubject(subjects[i])->getSubject();
       QString pathMask = currentDataset->getSubject(subjects[i])->getMask();
       QFileInfo dataFile(pathData);
       QFileInfo maskFile(pathMask);
       bool dataValid = dataFile.exists();
       bool maskValid = true;
       if(!pathMask.isEmpty())
            maskValid = maskFile.exists();
       if(!(maskValid && dataValid)){
           validSubjects = false;
           if(!dataValid){message.append( pathData +"\n");}
           if(!maskValid){message.append( pathMask+ "\n");}
       }
   }

   if(!validSubjects){
       QMessageBox msgBox(this);
       msgBox.setIcon(QMessageBox::Critical);
       msgBox.setText(message);
       msgBox.exec();
   }
    bool checkedOk = true;
   if(validSubjects && (protocol.isEmpty() || subjects.isEmpty())){
       checkedOk = false;
       QMessageBox msgBox(this);
       msgBox.setIcon(QMessageBox::Critical);
       msgBox.setText("Check at least one Subject and select one Protocol");
       msgBox.exec();
}

    if(validSubjects && checkedOk)
        emit this->executeAnalysis(protocol,subjects,resultsPath,viewResults,viewFeatures,saveFeatures,format);

}
