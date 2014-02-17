#include "filesystemexplorer.h"
#include "ui_filesystemexplorer.h"
using namespace romeo::view::mainWindow;
FileSystemExplorer::FileSystemExplorer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FileSystemExplorer)
{
    ui->setupUi(this);

    dirModel = new QFileSystemModel(this);
    dirModel->setFilter(QDir::NoDotAndDotDot | QDir::AllDirs);
    ui->treeView->setModel(dirModel);
    ui->treeView->setRootIndex(dirModel->setRootPath(QDir::homePath()));
    ui->treeView->hideColumn(1);
    ui->treeView->hideColumn(2);
    ui->treeView->hideColumn(3);



    fileModel = new QFileSystemModel(this);
    fileModel->setFilter(QDir::NoDotAndDotDot | QDir::Files);
    QStringList filters;
    filters << "*.jpg" <<"*.png";
    fileModel->setNameFilters(filters);
    fileModel->setNameFilterDisables(false);

    ui->listView->setModel(fileModel);
    ui->listView->setRootIndex(fileModel->setRootPath(QDir::homePath()));
    connect(ui->treeView,SIGNAL(clicked(QModelIndex)),this,SLOT(treeView_clicked(QModelIndex)));
}

FileSystemExplorer::~FileSystemExplorer()
{
    delete ui;
}

void FileSystemExplorer::treeView_clicked(QModelIndex index)
{
    QString aPath = dirModel->fileInfo(index).absoluteFilePath();
       fileModel->setFilter(QDir::NoDotAndDotDot | QDir::Files);
    ui->listView->setRootIndex(fileModel->setRootPath(aPath));
}
