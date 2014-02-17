/**
* \file protocolspanel.h
* \author Alessandro Strenghetto
* \date 2014-02-17
**
* \brief Header della classe ProtocolsPanel del package romeo::view::mainWindow
*/
#ifndef PROTOCOLSPANEL_H
#define PROTOCOLSPANEL_H

#include <QWidget>

namespace Ui {
class ProtocolsPanel;
}
namespace romeo {
namespace view {
namespace mainWindow{
class ProtocolsPanel : public QWidget
{
    Q_OBJECT

public:
    explicit ProtocolsPanel(QWidget *parent = 0);
    ~ProtocolsPanel();

private:
    Ui::ProtocolsPanel *ui;
};
}}}
#endif // PROTOCOLSPANEL_H
