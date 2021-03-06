/**
* \file subjectspanel.cpp
* \author Alessandro Strenghetto
* \date 2014-02-17
**
* \brief Header della classe SubjectsPanel del package romeo::view::mainWindow
*/

#include "subjectspanel.h"
#include "ui_subjectspanel.h"
#include <QString>
#include <QDrag>
#include <QMimeData>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QDragLeaveEvent>
#include <QDragMoveEvent>
#include <QFileInfo>
#include <QDebug>
#include <QFontMetrics>
#include <QMessageBox>

using namespace romeo::view::mainWindow;
using namespace romeo::model::datasets;

SubjectsPanel::SubjectsPanel(QWidget *parent) :
    QWidget(parent), currentDataset(0),
    ui(new Ui::SubjectsPanel)
{
    ui->setupUi(this);

    ui->subjectsList->setColumnCount(3);
    ui->subjectsList->setHeaderLabels(QStringList()<< "Name"<<"Data"<<"Mask");
    ui->subjectsList->setColumnWidth(0,160);
    ui->subjectsList->setColumnWidth(1,190);

    connectUI();
}

SubjectsPanel::~SubjectsPanel(){
        delete ui;
}

void SubjectsPanel::connectUI(){
    connect(ui->newButton,SIGNAL(clicked()),this,SIGNAL(openAddSubjectDialog()));
    connect(ui->deleteButton,SIGNAL(clicked()),this,SLOT(onDeleteClicked()));
}

void SubjectsPanel::AddSubject(QString name, QString dataFileName, QString maskFileName){

    QTreeWidgetItem *itm =new QTreeWidgetItem(ui->subjectsList);
    itm->setText(0,name);
    itm->setText(1,QFileInfo(dataFileName).fileName());
    itm->setText(2,QFileInfo(maskFileName).fileName());
    itm->setFlags(itm->flags() | Qt::ItemIsUserCheckable);
    itm->setCheckState(0,Qt::Checked);
}


void SubjectsPanel::dragEnterEvent(QDragEnterEvent * event){
    event->accept();
}

void SubjectsPanel::dragLeaveEvent(QDragLeaveEvent * event){
    event->accept();

}
void SubjectsPanel::dragMoveEvent(QDragMoveEvent * event){
     event->accept();

}
void SubjectsPanel::dropEvent(QDropEvent * event){

    if (event->mimeData()->hasFormat("subject")) {
        event->accept();
        event->setDropAction(Qt::MoveAction);
        QString subject = event->mimeData()->data("subject");
        QStringList dataMask = subject.split("%%%");
        int index = ui->subjectsList->topLevelItemCount()+1;
        bool nameAvaible = false;
        QString subjectName;
        while(!nameAvaible){
            subjectName = QString("Subject ").append(QString::number(index));
            if(currentDataset->getSubject(subjectName)){
                ++index;
            }
            else{
                nameAvaible = true;
            }
        }

        if(dataMask.size() > 1){
            emit createNewSubject(subjectName, dataMask[0],dataMask[1]);
        }
    } else
        event->ignore();
}

AbstractDataset *SubjectsPanel::getCurrentDataset() const
{
    return currentDataset;
}

void SubjectsPanel::setCurrentDataset(AbstractDataset *dataset)
{
    if(currentDataset != 0){
        disconnect(currentDataset,SIGNAL(addedSubject(QString,QString,QString)),this,SLOT(AddSubject(QString,QString,QString)));
        disconnect(currentDataset,SIGNAL(removedSubject(QString)),this,SLOT(removeSubjectFromList(QString)));
        disconnect(currentDataset,SIGNAL(invalidSubject(QString)),this,SLOT(onInvalidSubject(QString)));
    }
    currentDataset = dataset;

    if(currentDataset != 0){
        connect(currentDataset,SIGNAL(addedSubject(QString,QString,QString)),this,SLOT(AddSubject(QString,QString,QString)));
        connect(currentDataset,SIGNAL(removedSubject(QString)),this,SLOT(removeSubjectFromList(QString)));
        connect(currentDataset,SIGNAL(invalidSubject(QString)),this,SLOT(onInvalidSubject(QString)));
    }
    fillSubjectsList();

}



void SubjectsPanel::fillSubjectsList(){
    ui->subjectsList->clear();
    if(currentDataset != 0){
        ui->newButton->setEnabled(true);
        ui->deleteButton->setEnabled(true);
        setAcceptDrops(true);
        QList<AbstractSubject*> subjects = currentDataset->getSubjectList();
        for(int i = 0; i< subjects.size(); i++){
            AbstractSubject* subject = subjects[i];
            QString data = subject->getSubject();
            QString mask = subject->getMask();
            AddSubject(subject->getName(), data, mask);
        }

    }
    else{
        setAcceptDrops(false);
        ui->newButton->setEnabled(false);
        ui->deleteButton->setEnabled(false);
    }
}


void SubjectsPanel::onDeleteClicked(){
    QList<QTreeWidgetItem*> selectedSubject =ui->subjectsList->selectedItems();
    if(!selectedSubject.isEmpty()){
       QString subjectName = selectedSubject.at(0)->data(0,Qt::DisplayRole).toString();
       emit deleteSubject(subjectName);
    }
}

void SubjectsPanel::removeSubjectFromList(QString subjectName){
    QList<QTreeWidgetItem*> subject = ui->subjectsList->findItems(subjectName,Qt::MatchExactly,0);
    if(!subject.isEmpty()){
       delete subject[0];
    }
}

QList<QString> SubjectsPanel::getCheckedSubjects(){
    QList<QString> subjectsName;
    for (int i = 0; i < ui->subjectsList->topLevelItemCount(); i++){
        QTreeWidgetItem* item = ui->subjectsList->topLevelItem(i);
        if(item->checkState(0) == Qt::Checked){
            subjectsName.append(item->data(0,Qt::DisplayRole).toString());

        }
    }
    return subjectsName;

}

void SubjectsPanel::onInvalidSubject(QString messageError){
    QMessageBox msgBox;
    msgBox.setIcon(QMessageBox::Critical);
    msgBox.setText("ERR 0x24C9E96A");
    msgBox.setInformativeText(messageError);
    msgBox.exec();
}

