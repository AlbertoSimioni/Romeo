#include "src/romeo/view/mainWindow/mainwindow.h"
#include <QApplication>
#include <src/romeo/view/dialogs/protocoldialog.h>
#include<src/romeo/view/dialogs/newalgorithmdialog.h>
#include <src/romeo/view/dialogs/executedialog.h>
#include<src/romeo/view/dialogs/newfeaturedialog.h>
#include<src/romeo/view/dialogs/addsubjectdialog.h>
using namespace romeo::view::dialogs;
using namespace romeo::view::mainWindow;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    w.show();
    ProtocolDialog p;
    p.show();
    NewAlgorithmDialog n;
    n.show();
    NewFeatureDialog nf;
    nf.show();
    ExecuteDialog e;
    e.show();
    AddSubjectDialog ad;
    ad.show();
    return a.exec();
}
