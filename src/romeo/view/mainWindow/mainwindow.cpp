#include "mainwindow.h"
#include "ui_mainwindow.h"
using namespace romeo::view::mainWindow;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->sidebarFrame->setTabText(0, "Explorer");
    ui->sidebarFrame->setTabText(1, "File System");

}

MainWindow::~MainWindow()
{
    delete ui;
}


