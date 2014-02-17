/**
* \file executepanel.h
* \author Alessandro Strenghetto
* \date 2014-02-17
**
* \brief Header della classe ExecutePanel del package romeo::view::mainWindow
*/
#ifndef EXECUTEPANEL_H
#define EXECUTEPANEL_H

#include <QWidget>

namespace Ui {
class ExecutePanel;
}
namespace romeo{
namespace view {
namespace mainWindow{
class ExecutePanel : public QWidget
{
    Q_OBJECT

public:
    explicit ExecutePanel(QWidget *parent = 0);
    ~ExecutePanel();

private:
    Ui::ExecutePanel *ui;
};
}}}
#endif // EXECUTEPANEL_H
