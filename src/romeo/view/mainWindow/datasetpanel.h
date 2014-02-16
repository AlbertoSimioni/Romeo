#ifndef DATASETPANEL_H
#define DATASETPANEL_H

#include <QWidget>

namespace Ui {
class DatasetPanel;
}

class DatasetPanel : public QWidget
{
    Q_OBJECT

public:
    explicit DatasetPanel(QWidget *parent = 0);
    ~DatasetPanel();

private:
    Ui::DatasetPanel *ui;
};

#endif // DATASETPANEL_H
