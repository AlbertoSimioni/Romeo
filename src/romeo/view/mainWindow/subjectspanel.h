/**
* \file subjectspanel.h
* \author Alessandro Strenghetto
* \date 2014-02-17
**
* \brief Header della classe SubjectsPanel del package romeo::view::mainWindow
*/
#ifndef SUBJECTSPANEL_H
#define SUBJECTSPANEL_H

#include <QWidget>
#include<QTreeWidget>
#include <src/romeo/model/datasets/abstractdataset.h>

namespace Ui {
class SubjectsPanel;
}

namespace romeo {
namespace view {
namespace mainWindow{
class SubjectsPanel : public QWidget
{
    Q_OBJECT

public:
    explicit SubjectsPanel(QWidget *parent = 0);
    ~SubjectsPanel();


    void AddSubject(QString name, QString dataFileName, QString maskFileName);
    //void AddChild(QTreeWidgetItem *parent, QString protocolName);

    /*!
     * \brief Ritorna il riferimento al dataset corrente
     */
    romeo::model::datasets::AbstractDataset *getCurrentDataset() const;
    /*!
     * \brief Cambia il riferimento al dataset corrente
     */
    void setCurrentDataset(romeo::model::datasets::AbstractDataset *dataset);
signals:
    /*!
     * \brief Segnale emesso quando l'utente preme il tasto per la creazione di un nuovo subject
     */
    void openAddSubjectDialog();


protected:
    virtual void dragEnterEvent(QDragEnterEvent * event);
    virtual void dragLeaveEvent(QDragLeaveEvent * event);
    virtual void dragMoveEvent(QDragMoveEvent * event);
    virtual void dropEvent(QDropEvent * event);
private:



    /*!
     * \brief Effettua le connessioni dei segnali inviati dai vari widget che compongono la classe SubjectsPanel
     */
    void connectUI();

    void fillSubjectsList();

    /*!
     * \brief Riferimento al dataset attualmente attivo nella schermata
     */
    romeo::model::datasets::AbstractDataset* currentDataset;

    Ui::SubjectsPanel *ui;
};
}}}
#endif // SUBJECTSPANEL_H
