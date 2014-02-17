#include "executepanel.h"
#include "ui_executepanel.h"
using namespace romeo::view::mainWindow;
ExecutePanel::ExecutePanel(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ExecutePanel)
{
    ui->setupUi(this);
}

ExecutePanel::~ExecutePanel()
{
    delete ui;
}
