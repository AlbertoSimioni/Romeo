#include "filesystemexplorer.h"
#include "ui_filesystemexplorer.h"
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
    ui->foldersView->setRootIndex(dirModel->setRootPath(QDir::homePath()));
    ui->foldersView->hideColumn(1);
    ui->foldersView->hideColumn(2);
    ui->foldersView->hideColumn(3);



    fileModel = new QFileSystemModel(this);
    fileModel->setFilter(QDir::NoDotAndDotDot | QDir::Files);
    changeFilters();


    ui->filesView->setModel(fileModel);
    ui->filesView->setRootIndex(fileModel->setRootPath(QDir::homePath()));
    connect(ui->foldersView,SIGNAL(clicked(QModelIndex)),this,SLOT(treeView_clicked(QModelIndex)));

}


FileSystemExplorer::~FileSystemExplorer()
{
    delete ui;
}

void FileSystemExplorer::treeView_clicked(QModelIndex index)
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
    case TYPE2DT: filters << "*.avi";
        break;
    case TYPE3D: filters << "*.hdr" <<"*.nii";
        break;
    case TYPE3DT: filters << "*.hdr" <<"*.nii";
        break;
    }
    fileModel->setNameFilters(filters);
    fileModel->setNameFilterDisables(false);
}

