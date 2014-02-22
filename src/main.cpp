#include "src/romeo/view/mainWindow/mainwindow.h"
#include <QApplication>
#include <src/romeo/view/dialogs/protocoldialog.h>
#include<src/romeo/view/dialogs/newalgorithmdialog.h>
#include <src/romeo/view/dialogs/executedialog.h>
#include<src/romeo/view/dialogs/newfeaturedialog.h>
#include<src/romeo/view/dialogs/addsubjectdialog.h>
#include<src/romeo/controller/controller.h>
using namespace romeo::view::dialogs;
using namespace romeo::controller;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Controller* controller = Controller::getInstance();
   /* ProtocolDialog p;
    p.show();
    NewAlgorithmDialog n;
    n.show();
    NewFeatureDialog nf;
    nf.show();
    ExecuteDialog e;
    e.show();
    AddSubjectDialog ad;
    ad.show();*/
    int i =a.exec();
    delete controller;
    return i;
}
