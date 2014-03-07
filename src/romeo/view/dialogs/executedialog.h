/**
* \file executedialog.h
* \author Alessandro Strenghetto
* \date 2014-02-17
**
* \brief Header della classe ExecuteDialog del package romeo::view::dialogs
*/

#ifndef EXECUTEDIALOG_H
#define EXECUTEDIALOG_H

#include <QDialog>
#include <src/romeo/model/datasets/abstractdataset.h>
namespace Ui {
class ExecuteDialog;
}

namespace romeo {
namespace view {
namespace dialogs {


class ExecuteDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ExecuteDialog(QWidget *parent = 0);
    ~ExecuteDialog();

    void closeEvent(QCloseEvent *event);



    void prepareAnalysis(romeo::model::datasets::AbstractDataset *dataset,bool viewResults,bool viewFeatures,int numberSubjects, int nImages);


signals:
    /*!
     * \brief Segnale emesso dal dialogo per avvertire il model di interrompere le analisi.
     */
    void abortAnalysis();

private slots:

    /*!
     * \brief Slot che si preoccupa di abilitare il pulsante close e di impostare la linea di testo che indica lo stato delle analisi a "Completed"
     * in caso non siano stati analizzati tutti i subject altrimenti la imposta a canceled
     */
    void analysisFinished();


    /*!
     * \brief Slot che disabilita la pressione del tasto cancel ed invia il segnale cancelAnalysis() per avvertire il model di interrompere le analisi
     */
    void  onCancelClicked();

    /*!
     * \brief Slot che recupera dalla lista dei risultati quello successivo al corrente e lo mostra nella finestra
     * contenente i risultati
     */
    void onNextClicked();

    /*!
     * \brief Slot che recupera dalla lista dei risultati quello precedente al corrente e lo mostra nella finestra
     * contenente i risultati
     */
    void onPreviousClicked();

    /*!
     * \brief Slot che si preoccupa di aggiungere alla lista dei risultati il risultato dato in input
     */
    void addResultImage(QString pathToResult);




private:

    /*!
     * \brief Effettua le connessioni dei segnali inviati dai vari widget che compongono la classe ExecuteDialog
     */
    void connectUI();

    /*!
     * \brief Riporta il dialogo allo stato di creazione, e svuota la lista dei risultati
     */
    void clearDialog();

    /*!
     * \brief Mostra nel widget principale del dialogo l'immagine il cui percorso è dato in input
     */
    void showImage(QString pathToImage);

    Ui::ExecuteDialog *ui;

    /*!
     * \brief Percorsi alle immagini su disco corrispondenti ai risultati delle analisi in corso.
     */
    QList<QString> currentImagesPath;

    /*!
     * \brief dataset su cui si stanno effettuando o sono già state effettuate le analisi.
     */

    romeo::model::datasets::AbstractDataset* currentDataset;

    /*!
     * \brief Campo dati che indica se i risultati dell'esecuzione dell'algoritmo sono da visualizzare a meno
     */
    bool visualizeResults;

    /*!
     * \brief Campo dati che indica se i risultati ricavati dall'esecuzione dei feature extractor sono da visualizzare o meno.
     */
    bool visualizeFeatures;

    /*!
     * \brief campo dati contenente il numero dell'immagine correntemente visualizzata
     */
    int currentIndex;

    /*!
     * \brief Numero di subject sui cui si stanno effettuando le analisi
     */
    int nSubjects;

    /*!
     * \brief Numero di immagini da visualizzare per subject
     */
    int nImagesPerSubject;

};
}}}


#endif // EXECUTEDIALOG_H
