/**
* \file mainwindow.h
* \author Alessandro Strenghetto
* \date 2014-02-17
**
* \brief Header della classe MainWindow del package romeo::view::mainWindow
*/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

namespace romeo{
namespace view{
namespace mainWindow {
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

signals:
    void openNewDatasetDialog();
    void openNewPortocolDialog();
    void openNewAlgorithmDialog();



private slots:

private:
    Ui::MainWindow *ui;
    /*!
     * \brief Il metodo collega le varie QAction della main window con l'emissione dei segnali della MainWindow
     */
    void connectActionsToSignal();
};
}}}
#endif // MAINWINDOW_H
