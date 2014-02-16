#ifndef PROTOCOLSEXPLORER_H
#define PROTOCOLSEXPLORER_H

#include <QWidget>

namespace Ui {
class ProtocolsExplorer;
}

class ProtocolsExplorer : public QWidget
{
    Q_OBJECT

public:
    explicit ProtocolsExplorer(QWidget *parent = 0);
    ~ProtocolsExplorer();

private:
    Ui::ProtocolsExplorer *ui;
};

#endif // PROTOCOLSEXPLORER_H
