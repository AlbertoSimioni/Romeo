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
#include<src/romeo/model/inputformats.h>
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

    /*!
     * \brief Cambia il formato corrente dei dati in input
     */
    void setCurrentInputFormat(const romeo::model::InputFormat &value);

public slots:
    void treeViewClicked(QModelIndex index);


private:
    /*!
     * \brief Cambia i filtri sulle estensioni dei file da visualizzare in base al formato di input corrente
     */
    void changeFilters();
    /*!
     * \brief Tipo delle immagini che possono essere associate al dataset correntemente visualizzato
     */
    romeo::model::InputFormat currentInputFormat;
    Ui::FileSystemExplorer *ui;
    QFileSystemModel *dirModel;
    QFileSystemModel *fileModel;
};
}}}
#endif // FILESYSTEMEXPLORER_H
