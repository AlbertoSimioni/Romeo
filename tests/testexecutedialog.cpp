#include "testexecutedialog.h"
#include "ui_executedialog.h"
#include <QPushButton>

TestExecuteDialog::TestExecuteDialog(QObject *parent) :
    QObject(parent)
{
}

void TestExecuteDialog::showImage(){
    ExecuteDialog *exDialogTest1=new ExecuteDialog(0);
    QString datasetName="DatasetProva";
    romeo::model::datasets::AbstractDataset *dat2d=new romeo::model::datasets::Dataset2D(datasetName);
    exDialogTest1->prepareAnalysis(dat2d,false,false,2,1,2);
    QDir image = QDir::current();
    image.cd("..");
    image.cd("..");
    image.cd("tests");
    image.cd("images");
    exDialogTest1->showImage(image.absolutePath().append("/image.png"));

    ExecuteDialog *exDialogTest2=new ExecuteDialog(0);
    QString datasetName2="DatasetProva";
    romeo::model::datasets::AbstractDataset *dat3d=new romeo::model::datasets::Dataset3D(datasetName2);
    exDialogTest2->prepareAnalysis(dat3d,false,false,2,1,2);
    exDialogTest2->showImage(image.absolutePath().append("/image3d_K-means.nii"));
  /*  delete exDialogTest2;
    delete dat2d;
    delete dat3d;
*/
}


//QTEST_MAIN(TestExecuteDialog)
