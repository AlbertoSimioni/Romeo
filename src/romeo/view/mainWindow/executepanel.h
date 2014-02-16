#ifndef EXECUTEPANEL_H
#define EXECUTEPANEL_H

#include <QWidget>

namespace Ui {
class ExecutePanel;
}

class ExecutePanel : public QWidget
{
    Q_OBJECT

public:
    explicit ExecutePanel(QWidget *parent = 0);
    ~ExecutePanel();

private:
    Ui::ExecutePanel *ui;
};

#endif // EXECUTEPANEL_H
