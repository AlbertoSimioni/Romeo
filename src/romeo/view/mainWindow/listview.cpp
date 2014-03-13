/**
* \file listview.h
* \author Alessandro Strenghetto
* \date 2014-02-17
**
* \brief Header della classe ListView del package romeo::view::mainWindow
*/

#include "listview.h"
using namespace romeo::view::mainWindow;
#include<QMimeData>
#include<QByteArray>
#include<QDrag>
#include<QFileSystemModel>

ListView::ListView(QWidget *parent) :
    QListView(parent)
{
    setSelectionMode(QAbstractItemView::ExtendedSelection);
    setDragEnabled(true);

}
void ListView::startDrag(Qt::DropActions)
{
    QString list;
    QFileSystemModel* fileModel = dynamic_cast<QFileSystemModel*>(model());

    foreach(const QModelIndex &index, selectionModel()->selectedIndexes()){
        QString content = fileModel->filePath(index);
        list += (content.append("%%%"));
    }
    QMimeData *mimeData = new QMimeData;
    QByteArray ba = list.toUtf8().data();
    QString theText = "subject";
    mimeData->setData(theText, ba);
    QDrag *drag = new QDrag(this);
    drag->setMimeData(mimeData);
    drag->exec(Qt::MoveAction);
}

