#ifndef PROTOCOLSPANEL_H
#define PROTOCOLSPANEL_H

#include <QWidget>

namespace Ui {
class ProtocolsPanel;
}

class ProtocolsPanel : public QWidget
{
    Q_OBJECT

public:
    explicit ProtocolsPanel(QWidget *parent = 0);
    ~ProtocolsPanel();

private:
    Ui::ProtocolsPanel *ui;
};

#endif // PROTOCOLSPANEL_H
