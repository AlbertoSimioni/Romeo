#ifndef LISTWIDGET_H
#define LISTWIDGET_H

#include <QListWidget>
namespace romeo{
namespace view{
namespace mainWindow {

/*!
 * \brief Sottoclasse di QListWidget, necessaria per implementare la funzione di drag & drop
 */
class ListWidget : public QListWidget
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
