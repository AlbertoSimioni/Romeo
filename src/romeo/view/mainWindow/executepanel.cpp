#include "executepanel.h"
#include "ui_executepanel.h"

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
