/**
* \file explorer.h
* \author Alessandro Strenghetto
* \date 2014-02-17
**
* \brief Header della classe Explorer del package romeo::view::mainWindow
*/
#ifndef EXPLORER_H
#define EXPLORER_H

#include <QWidget>

namespace Ui {
class Explorer;
}
namespace romeo {
namespace view {
namespace mainWindow{
class Explorer : public QWidget
{
    Q_OBJECT

public:
    explicit Explorer(QWidget *parent = 0);
    ~Explorer();

private:
    Ui::Explorer *ui;
};
}}}

#endif // EXPLORER_H
