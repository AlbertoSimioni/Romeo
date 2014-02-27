#include "subjectspanel.h"
#include "ui_subjectspanel.h"
#include <QString>
#include <QDrag>
#include <QMimeData>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QDragLeaveEvent>
#include <QDragMoveEvent>
using namespace romeo::view::mainWindow;
using namespace romeo::model::datasets;

SubjectsPanel::SubjectsPanel(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SubjectsPanel)
{
    ui->setupUi(this);

    ui->subjectsList->setColumnCount(3);
    ui->subjectsList->setHeaderLabels(QStringList()<< "Name"<<"Data"<<"Mask");
    setAcceptDrops(true);
    AddRoot("Subject 1","image.png","mask1.png");
    AddRoot("Subject 2","data.jpg","mask.jpg");
    AddRoot("Subject 3","ann_o.bmp","0.bmp");
    AddRoot("Subject 4","4.tif","4_mask.png");

    connectUI();

    }

SubjectsPanel::~SubjectsPanel(){
        delete ui;
}

void SubjectsPanel::connectUI(){
    connect(ui->newButton,SIGNAL(clicked()),this,SIGNAL(openAddSubjectDialog()));
}

void SubjectsPanel::AddRoot(QString name, QString dataFileName, QString maskFileName){

    QTreeWidgetItem *itm =new QTreeWidgetItem(ui->subjectsList);
    itm->setText(0,name);
    itm->setText(1,dataFileName);
    itm->setText(2,maskFileName);
    itm->setFlags(itm->flags() | Qt::ItemIsUserCheckable);
    itm->setCheckState(0,Qt::Checked);

    AddChild(itm,"Result Protocol 1");
    AddChild(itm,"Result Protocol 2");
}

void SubjectsPanel::AddChild(QTreeWidgetItem *parent,QString protocolName){
     QTreeWidgetItem *itm =new QTreeWidgetItem();
     itm->setText(0,protocolName);
     parent->addChild(itm);
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
        QString name = "Subject ";
        name += QString::number(index);
        if(dataMask.size() > 1){
            AddRoot(name, dataMask[0].split("/").last(),dataMask[1].split("/").last());
        }
        /*else if (dataMask.size() == 1){
            AddRoot(name,dataMask[0].split("/").last(),QString());
        }
    */
    } else
        event->ignore();
}

AbstractDataset *SubjectsPanel::getCurrentDataset() const
{
    return currentDataset;
}

void SubjectsPanel::setCurrentDataset(AbstractDataset *dataset)
{
    currentDataset = dataset;
}



void SubjectsPanel::fillSubjectsList(){
  /*  ui->subjectsList->clear();

    QList<QString> subjects = currentDataset->getSubjectList();
    for(int i = 0; i< subjects.size(); i++){

    }
*/
}
