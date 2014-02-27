#ifndef LISTVIEW_H
#define LISTVIEW_H

#include <QListView>
namespace romeo{
namespace view{
namespace mainWindow {

/*!
 * \brief Sottoclasse di QListView, necessaria per implementare la funzione di drag & drop
 */
class ListView : public QListView
{
    Q_OBJECT
public:
    explicit ListView(QWidget *parent = 0);

signals:
    void startingDrag();
protected:
    void startDrag(Qt::DropActions);
signals:

public slots:

};
}}}
#endif // LISTVIEW_H
