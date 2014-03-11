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
#include "vtkImageViewer2.h"
#include "vtkSmartPointer.h"


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


    /*!
     * \brief Metodo che esegue delle operazioni di preparazione all'esecuzione come il ripristino della finestra di dialogo in cui visualizzare le immagini risultato e la raccolta dei dati fondamentali per far partire l'esecuzione di un protocollo. Inoltre si preoccupa di disconnettere segnali precedentemente impostati se presenti.
     * \param dataset Il dataset che contiene i dati da analizzare.
     * \param viewResults Valore booleano impostato a true se si vogliono visualizzare i risultati al termine dell'esecuzione.
     * \param viewFeatures Valore booleano impostato a true se si vogliono visualizzare le feature estratte durante l'esecuzione.
     * \param numberSubjects Il numero du subject da analizzare.
     * \param nAlgorithms Numero di algoritmi (può essere uno oppure zero).
     * \param nFeatures Numero di features da analizzare.
     */
    void prepareAnalysis(romeo::model::datasets::AbstractDataset *dataset,bool viewResults,bool viewFeatures,int numberSubjects,int nAlgorithms, int nFeatures);


signals:
    /*!
     * \brief Segnale emesso dal dialogo per avvertire il model di interrompere le analisi.
     */
    void abortAnalysis();

private slots:

    /*!
     * \brief Slot avviato dopo l'avvenuta estrazione di una feature, si preoccupa di aggiornare la percentuale delle analisi e in caso l'utente abbia
     * deciso di visualizzare le feature anche di invocare il metodo addResultImage per l'aggiunta dell'immagine ai risultati da visualizzare
     */
    void onFeatureExtracted(QString pathToFeature);

    /*!
     * \brief Slot avviato dopo l'avvenuta esecuzione di un algoritmo, si preoccupa di aggiornare la percentuale delle analisi e in caso l'utente abbia
     * deciso di visualizzare le feature anche di invocare il metodo addResultImage per l'aggiunta dell'immagine ai risultati da visualizzare
     */
    void onAlgorithmExecuted(QString pathToAlgorithm);

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

    /*!
     * \brief Slot avviato quando l'utente preme il pulsante per non visualizzare più le feature, setta a false il campo dati visualizeFeatures
     */
    void onNoFeatureClicked();


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
     * \brief Numero di immagini da calcolare per subject
     */
    int nImagesPerSubject;



    vtkSmartPointer<vtkImageViewer2> image_view;

};
}}}


#endif // EXECUTEDIALOG_H
