/**
* \file listwidget.h
* \author Alessandro Strenghetto
* \date 2014-02-17
**
* \brief Header della classe ListWidget del package romeo::view::mainWindow
*/


#include "listwidget.h"
#include <QMimeData>
#include <QDrag>
#include <QMenu>
#include <QDebug>


using namespace romeo::view::mainWindow;
ListWidget::ListWidget(QWidget *parent) :
    QTreeWidget(parent)
{
    this->setIndentation(0);
    associateAction=new QAction("Associate to Dataset", this);
    deleteProtocol=new QAction("Delete",this);
}

void ListWidget::startDrag(Qt::DropActions)
{
    QTreeWidgetItem *item = currentItem();
    QMimeData *mimeData = new QMimeData;
    QByteArray ba = item->data(0,Qt::EditRole).toString().toUtf8().data();
    QString theText = "protocol";
    mimeData->setData(theText, ba);
    QDrag *drag = new QDrag(this);
    drag->setMimeData(mimeData);
    drag->exec(Qt::MoveAction);
}

void ListWidget::contextMenuEvent(QContextMenuEvent *e){
    QTreeWidgetItem* item=this->itemAt(e->pos());
    if(item){
        QMenu m(this);
        m.addAction(associateAction);
        m.addAction(deleteProtocol);
        m.exec(e->globalPos());
    }
}
