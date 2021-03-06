#include "src/romeo/view/mainWindow/mainwindow.h"
#include <QApplication>
#include<src/romeo/controller/controller.h>

using namespace romeo::view::dialogs;
using namespace romeo::controller;

int main(int argc, char *argv[])
{
    QApplication romeoApp(argc, argv);
    QCoreApplication::setOrganizationName("Hurry Up!");
    QCoreApplication::setApplicationName("ROMEO");
    DatasetsController* controller = DatasetsController::getInstance();

    int returnValue =romeoApp.exec();
    delete controller;
    return returnValue;
}
