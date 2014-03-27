/**
* \file listwidget.h
* \author Alessandro Strenghetto
* \date 2014-02-17
**
* \brief Header della classe ListWidget del package romeo::view::mainWindow
*/

#ifndef LISTWIDGET_H
#define LISTWIDGET_H

#include <QTreeWidget>
#include <QContextMenuEvent>

namespace romeo{
namespace view{
namespace mainWindow {

/*!
 * \brief Sottoclasse di QListWidget, necessaria per implementare la funzione di drag & drop
 */
class ListWidget : public QTreeWidget
{
    Q_OBJECT
public:
    explicit ListWidget(QWidget *parent = 0);
    QAction* associateAction;
    QAction* deleteProtocol;
protected:
    void startDrag(Qt::DropActions);
    void contextMenuEvent(QContextMenuEvent *e);
signals:

public slots:
};
}}}
#endif // LISTWIDGET_H
