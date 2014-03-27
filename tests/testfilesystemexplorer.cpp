#include "testfilesystemexplorer.h"
#include "ui_filesystemexplorer.h"
#include <QPushButton>

TestFileSystemExplorer::TestFileSystemExplorer(QObject *parent) :
    QObject(parent)
{
}

void TestFileSystemExplorer::setCurrentInputFormat(){
    FileSystemExplorer *fse = new FileSystemExplorer();
    romeo::model::InputFormat format;

    format = romeo::model::TYPE2D;
    fse->setCurrentInputFormat(format);
    QCOMPARE(fse->currentInputFormat,format);

    format = romeo::model::TYPE2DT;
    fse->setCurrentInputFormat(format);
    QCOMPARE(fse->currentInputFormat,format);

    format = romeo::model::TYPE3D;
    fse->setCurrentInputFormat(format);
    QCOMPARE(fse->currentInputFormat,format);

    format = romeo::model::TYPE3DT;
    fse->setCurrentInputFormat(format);
    QCOMPARE(fse->currentInputFormat,format);

    delete fse;
}

void TestFileSystemExplorer::changeFilters(){
    FileSystemExplorer *fse = new FileSystemExplorer();
    QStringList filters;

    fse->currentInputFormat = romeo::model::TYPE2D;
    fse->changeFilters();
    QCOMPARE(fse->fileModel->nameFilters(), filters << "*.jpg" <<"*.png" <<"*.bmp" <<"*.tiff" <<"*.tif");

    filters.clear();
    fse->currentInputFormat = romeo::model::TYPE2DT;
    fse->changeFilters();
    QCOMPARE(fse->fileModel->nameFilters(), filters << "*.avi" << "*.jpg" <<"*.png" <<"*.bmp" <<"*.tiff" <<"*.tif");

    filters.clear();
    fse->currentInputFormat = romeo::model::TYPE3D;
    fse->changeFilters();
    QCOMPARE(fse->fileModel->nameFilters(), filters << "*.hdr" <<"*.nii");

    filters.clear();
    fse->currentInputFormat = romeo::model::TYPE3DT;
    fse->changeFilters();
    QCOMPARE(fse->fileModel->nameFilters(), filters << "*.hdr" <<"*.nii");

    delete fse;
}
