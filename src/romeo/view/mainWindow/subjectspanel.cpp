#include "subjectspanel.h"
#include "ui_subjectspanel.h"

SubjectsPanel::SubjectsPanel(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SubjectsPanel)
{
    ui->setupUi(this);

    ui->treeWidget->setColumnCount(3);
    ui->treeWidget->setHeaderLabels(QStringList()<< "Name"<<"Data"<<"Mask");
    AddRoot("Subject 1","image.png","mask1.png");
    AddRoot("Subject 2","data.jpg","mask.jpg");
    AddRoot("Subject 3","ann_o.bmp","0.bmp");
    AddRoot("Subject 4","4.tif","4_mask.png");

    }

SubjectsPanel::~SubjectsPanel(){
        delete ui;
}
void SubjectsPanel::AddRoot(QString name, QString dataFileName, QString maskFileName){

    QTreeWidgetItem *itm =new QTreeWidgetItem(ui->treeWidget);
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
