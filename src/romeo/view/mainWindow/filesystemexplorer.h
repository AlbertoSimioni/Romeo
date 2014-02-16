#ifndef FILESYSTEMEXPLORER_H
#define FILESYSTEMEXPLORER_H

#include <QWidget>
#include<QFileSystemModel>
namespace Ui {
class FileSystemExplorer;
}

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

#endif // FILESYSTEMEXPLORER_H
