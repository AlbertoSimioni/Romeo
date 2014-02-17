/**
* \file datasetexplorer.h
* \author Alessandro Strenghetto
* \date 2014-02-17
**
* \brief Header della classe DatasetExplorer del package romeo::view::mainWindow
*/

#ifndef DATASETSEXPLORER_H
#define DATASETSEXPLORER_H

#include <QWidget>
namespace Ui {
class DatasetsExplorer;
}

namespace romeo{
namespace view{
namespace mainWindow{

class DatasetsExplorer : public QWidget
{
    Q_OBJECT

public:
    explicit DatasetsExplorer(QWidget *parent = 0);
    ~DatasetsExplorer();

private:
    Ui::DatasetsExplorer *ui;
};
}}}
#endif // DATASETSEXPLORER_H
