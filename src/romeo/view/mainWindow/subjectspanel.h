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

/*!
 * \brief Il pannello visualizza le informazioni sui subject attualmente contenuti nel dataset e quelli selezionati dall'utente.
 *
 * Permette di modificare la lista di subject nel dataset selezionato e di selezionare solo alcuni dei subject a cui sottoporre i protocolli. Fornisce all'esterno le informazioni sugli input utente e sui file immagine che vuole aggiungere al dataset.
 */
class SubjectsPanel : public QWidget
{
    Q_OBJECT

public:
    explicit SubjectsPanel(QWidget *parent = 0);
    ~SubjectsPanel();
    /*!
     * \brief Ritorna il riferimento al dataset corrente
     */
    romeo::model::datasets::AbstractDataset *getCurrentDataset() const;
    /*!
     * \brief Cambia il riferimento al dataset corrente
     */
    void setCurrentDataset(romeo::model::datasets::AbstractDataset *dataset);

    /*!
     * \brief Ritorna una lista contente i subjects correntemente selezionati
     */
    QList<QString> getCheckedSubjects();
signals:
    /*!
     * \brief Segnale emesso quando l'utente preme il tasto per la creazione di un nuovo subject
     */
    void openAddSubjectDialog();
    /*!
     * \brief Segnale emesso quando l'utente effettua un'azione di drag & drop per l'aggiunta di un nuovo subject
     * \param name
     * \param data
     * \param mask
     */
    void createNewSubject(QString name, QString data, QString mask);

    /*!
     * \brief deleteSubject
     * \param name
     */
    void deleteSubject(QString name);

protected:
    virtual void dragEnterEvent(QDragEnterEvent * event);
    virtual void dragLeaveEvent(QDragLeaveEvent * event);
    virtual void dragMoveEvent(QDragMoveEvent * event);
    virtual void dropEvent(QDropEvent * event);

private slots:
    /*!
     * \brief Slot che aggiunge un subject al widget che mostra la lista dei subject
     */
    void AddSubject(QString name, QString dataFileName, QString maskFileName);
    void removeSubjectFromList(QString subjectName);
    /*!
     * \brief Slot avviato alla pressione del tasto delete, si preoccupa di recuperare il nome del subject correntemente selezionato e di emettere il segnale deleteSubject()
     */
    void onDeleteClicked();
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
