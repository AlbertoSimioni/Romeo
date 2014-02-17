/**
* \file protocolsexplorer.h
* \author Alessandro Strenghetto
* \date 2014-02-17
**
* \brief Header della classe ProtocolsExplorer del package romeo::view::mainWindow
*/
#ifndef PROTOCOLSEXPLORER_H
#define PROTOCOLSEXPLORER_H

#include <QWidget>

namespace Ui {
class ProtocolsExplorer;
}
namespace romeo {
namespace view {
namespace mainWindow{
class ProtocolsExplorer : public QWidget
{
    Q_OBJECT

public:
    explicit ProtocolsExplorer(QWidget *parent = 0);
    ~ProtocolsExplorer();

private:
    Ui::ProtocolsExplorer *ui;
};
}}}
#endif // PROTOCOLSEXPLORER_H
