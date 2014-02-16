#ifndef DATASETSEXPLORER_H
#define DATASETSEXPLORER_H

#include <QWidget>

namespace Ui {
class DatasetsExplorer;
}

class DatasetsExplorer : public QWidget
{
    Q_OBJECT

public:
    explicit DatasetsExplorer(QWidget *parent = 0);
    ~DatasetsExplorer();

private:
    Ui::DatasetsExplorer *ui;
};

#endif // DATASETSEXPLORER_H
