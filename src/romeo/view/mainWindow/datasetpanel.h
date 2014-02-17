/**
* \file datasetpanel.h
* \author Alessandro Strenghetto
* \date 2014-02-17
**
* \brief Header della classe DatasetPanel del package romeo::view::mainWindow
*/

#ifndef DATASETPANEL_H
#define DATASETPANEL_H

#include <QWidget>
namespace Ui {
class DatasetPanel;
}

namespace romeo{
namespace view{
namespace mainWindow {

class DatasetPanel : public QWidget
{
    Q_OBJECT

public:
    explicit DatasetPanel(QWidget *parent = 0);
    ~DatasetPanel();

private:
    Ui::DatasetPanel *ui;
};
}}}
#endif // DATASETPANEL_H
