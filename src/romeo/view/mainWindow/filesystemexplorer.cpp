/**
* \file filesystemexplorer.cpp
* \author Alessandro Strenghetto
* \date 2014-02-17
**
* \brief Header della classe FileSystemExplorer del package romeo::view::mainWindow
*/

#include "filesystemexplorer.h"
#include "ui_filesystemexplorer.h"
#include <QSettings>
#ifdef WIN32
 #define WINDOWS
#elif WIN64
 #define WINDOWS
#endif



using namespace romeo::view::mainWindow;
using namespace romeo::model;

FileSystemExplorer::FileSystemExplorer(QWidget *parent) :
    QWidget(parent), currentInputFormat(TYPE2D),
    ui(new Ui::FileSystemExplorer)
{
    ui->setupUi(this);

    dirModel = new QFileSystemModel(this);
    dirModel->setFilter(QDir::NoDotAndDotDot | QDir::AllDirs);


    ui->foldersView->setModel(dirModel);
    #ifdef WINDOWS
        ui->foldersView->setRootIndex(dirModel->setRootPath(QDir::rootPath()));
    #else
        ui->foldersView->setRootIndex(dirModel->setRootPath(QDir::homePath()));
    #endif
    ui->foldersView->hideColumn(1);
    ui->foldersView->hideColumn(2);
    ui->foldersView->hideColumn(3);

    QSettings romeoSettings;
    QString currentPath = romeoSettings.value("currentPath").toString();
    if(currentPath.isEmpty())
        currentPath = dirModel->rootPath();
    ui->foldersView->setCurrentIndex(dirModel->index(currentPath));
    fileModel = new QFileSystemModel(this);
    fileModel->setFilter(QDir::NoDotAndDotDot | QDir::Files);
    changeFilters();


    ui->filesView->setModel(fileModel);
    QString aPath = dirModel->fileInfo(ui->foldersView->currentIndex()).absoluteFilePath();
    ui->filesView->setRootIndex(fileModel->setRootPath(aPath));
    connect(ui->foldersView,SIGNAL(clicked(QModelIndex)),this,SLOT(treeViewClicked(QModelIndex)));

}


FileSystemExplorer::~FileSystemExplorer()
{
    QSettings romeoSettings;
    romeoSettings.setValue("currentPath",dirModel->filePath(ui->foldersView->currentIndex()));
    delete ui;
}

void FileSystemExplorer::treeViewClicked(QModelIndex index)
{
    QString aPath = dirModel->fileInfo(index).absoluteFilePath();
       fileModel->setFilter(QDir::NoDotAndDotDot | QDir::Files);
    ui->filesView->setRootIndex(fileModel->setRootPath(aPath));
}


void FileSystemExplorer::setCurrentInputFormat(const romeo::model::InputFormat &value)
{
    currentInputFormat = value;
    changeFilters();
}

void FileSystemExplorer::changeFilters(){
    QStringList filters;
    switch(currentInputFormat){
    case TYPE2D: filters << "*.jpg" <<"*.png" <<"*.bmp" <<"*.tiff" <<"*.tif";
        break;
    case TYPE2DT: filters << "*.avi" << "*.jpg" <<"*.png" <<"*.bmp" <<"*.tiff" <<"*.tif";
        break;
    case TYPE3D: filters << "*.hdr" <<"*.nii";
        break;
    case TYPE3DT: filters << "*.hdr" <<"*.nii";
        break;
    }
    fileModel->setNameFilters(filters);
    fileModel->setNameFilterDisables(false);
}

