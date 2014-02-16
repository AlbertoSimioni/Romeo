#ifndef SUBJECTSPANEL_H
#define SUBJECTSPANEL_H

#include <QWidget>
#include<QTreeWidget>
namespace Ui {
class SubjectsPanel;
}

class SubjectsPanel : public QWidget
{
    Q_OBJECT

public:
    explicit SubjectsPanel(QWidget *parent = 0);
    ~SubjectsPanel();
    void AddRoot(QString name, QString dataFileName, QString maskFileName);
    void AddChild(QTreeWidgetItem *parent, QString protocolName);

private:
    Ui::SubjectsPanel *ui;
};

#endif // SUBJECTSPANEL_H
