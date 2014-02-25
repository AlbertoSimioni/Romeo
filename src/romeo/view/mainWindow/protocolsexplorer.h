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
#include <src/romeo/model/protocols/protocolslist.h>
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

    romeo::model::protocols::ProtocolsList *getProtocolsList() const;
    void setProtocolsList(romeo::model::protocols::ProtocolsList *value);

private:
    Ui::ProtocolsExplorer *ui;

    romeo::model::protocols::ProtocolsList* protocolsList;
};
}}}
#endif // PROTOCOLSEXPLORER_H
