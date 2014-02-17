/**
* \file filesystemexplorer.h
* \author Alessandro Strenghetto
* \date 2014-02-17
**
* \brief Header della classe FileSystemExplorer del package romeo::view::mainWindow
*/
#ifndef FILESYSTEMEXPLORER_H
#define FILESYSTEMEXPLORER_H

#include <QWidget>
#include<QFileSystemModel>
namespace Ui {
class FileSystemExplorer;
}
namespace romeo {
namespace view {
namespace mainWindow {
class FileSystemExplorer : public QWidget
{
    Q_OBJECT

public:
    explicit FileSystemExplorer(QWidget *parent = 0);
    ~FileSystemExplorer();

public slots:
    void treeView_clicked(QModelIndex index);

private:
    Ui::FileSystemExplorer *ui;
    QFileSystemModel *dirModel;
    QFileSystemModel *fileModel;
};
}}}
#endif // FILESYSTEMEXPLORER_H
