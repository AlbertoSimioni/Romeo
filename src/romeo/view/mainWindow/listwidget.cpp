#include "listwidget.h"
#include <QMimeData>
#include <QDrag>
using namespace romeo::view::mainWindow;
ListWidget::ListWidget(QWidget *parent) :
    QListWidget(parent)
{

}

void ListWidget::startDrag(Qt::DropActions)
{
    QListWidgetItem *item = currentItem();
    QMimeData *mimeData = new QMimeData;
    QByteArray ba = item->text().toLatin1().data();
    QString theText = "protocol";
    mimeData->setData(theText, ba);
    QDrag *drag = new QDrag(this);
    drag->setMimeData(mimeData);
    drag->exec(Qt::MoveAction);
}
