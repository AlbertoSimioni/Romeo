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
protected:
    void startDrag(Qt::DropActions);
signals:

public slots:

};
}}}
#endif // LISTWIDGET_H
