
/**
* \file analysiscontroller.h
* \author Matteo Pozza
* \date 2014-02-17
**
* \brief Header della classe AnalysisController del package romeo::controller
*/

#ifndef ANALYSISCONTROLLER_H
#define ANALYSISCONTROLLER_H

#include <QObject>
#include <src/romeo/view/mainWindow/executepanel.h>
#include<src/romeo/view/dialogs/executedialog.h>
#include<src/romeo/model/datasets/abstractdataset.h>
#include<src/romeo/view/mainWindow/mainwindow.h>

namespace romeo {
namespace controller{

/**
 * \brief La classe AnalysisController da completare
 *
 * Descrizione dettagliata
 */


class AnalysisController : public QObject
{
    Q_OBJECT
public:
    explicit AnalysisController(romeo::view::mainWindow::MainWindow* mainw = 0,QObject *parent = 0);

    /*!
     * \brief Cambia il dataset corrente sul dialogo di esecuzione
     * \param currDataset riferimento al dataset da impostare come dataset corrente
     */
    void changeExecuteDialogCurrentDataset(romeo::model::datasets::AbstractDataset* currDataset);


    /*!
     * \brief Metodo statico che ritorna l'istanza del controller, in caso sia la prima volta ad essere invocato
     *  si preoccupa anche di costruire l'istanza.
     */
    static AnalysisController* getInstance(romeo::view::mainWindow::MainWindow* mainw = 0,QObject* parent = 0);

private slots:
    /*!
     * \brief Slot che riceve in input i dati per l'esecuzione e invoca l'esecuzione sul dataset corrente
     * \param protocol Nome del protocollo da eseguire.
     * \param subjects Lista contenente i soggetti su cui fare l'analisi.
     * \param resultsPath Il percorso nel file system su cui salvare i risultati.
     * \param viewResults Parametro booleano che indica se visualizzare la cartella dei risultati al tremine dell'esecuzione.
     * \param viewFeatures Flag booleana che indica se visualizzare le feature estratte durante l'esecuzione.
     * \param saveFeatures Parametro booleano che indica se salvare su disco i risultati delle feature estratte.
     * \param format Il formato delle immagini da analizzare.
     */
    void startAnalysis(QString protocol,QList<QString> subjects,QString resultsPath,bool viewResults,bool viewFeatures,bool saveFeatures,QString format);

    /*!
     * \brief Slot che si preoccupa di abortire la analisi in esecuzione sul dataset corrente
     */
    void abortAnalysis();

private:

    /*!
     * \brief Metodo che collega i segnali emessi dul dialogo di esecuzioni agli slot della classe
     */
    void connectViewsSignals();


    /*!
     * \brief Campo dati statico che contiene il riferimento all'unica istanza del controller
     */
    static AnalysisController* instance;


    /*!
     * \brief Riferimento al dialogo per l'esecuzione di un protocollo
     */
    romeo::view::dialogs::ExecuteDialog* executeDialog;


    romeo::view::mainWindow::MainWindow* mainWindow;

};

}
}
#endif // ANALYSISCONTROLLER_H
