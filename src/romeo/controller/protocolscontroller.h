#ifndef PROTOCOLSCONTROLLER_H
#define PROTOCOLSCONTROLLER_H

#include <QObject>
#include<src/romeo/view/mainWindow/protocolsexplorer.h>
#include<src/romeo/view/mainWindow/protocolspanel.h>
#include<src/romeo/model/protocols/protocolslist.h>
#include<src/romeo/view/dialogs/protocoldialog.h>
#include<src/romeo/model/protocols/algorithms/algorithmslist.h>
#include<src/romeo/model/protocols/features/featureslist.h>
#include<src/romeo/view/dialogs/associateprotocoldialog.h>
#include<src/romeo/controller/algorithmscontroller.h>
#include<src/romeo/controller/featurescontroller.h>
#include<src/romeo/view/mainWindow/mainwindow.h>

namespace romeo {
namespace controller{


class ProtocolsController : public QObject
{
    Q_OBJECT
public:
    explicit ProtocolsController(romeo::view::mainWindow::MainWindow* mainw  = 0,QObject *parent = 0);
    /*!
     * \brief Metodo statico che ritorna l'istanza del controller, in caso sia la prima volta ad essere invocato
     *  si preoccupa anche di costruire l'istanza.
     */
    static ProtocolsController* getInstance(view::mainWindow::MainWindow *mainw =  0,QObject* parent = 0);


    /*!
     * \brief Metodo che cambia il tipo corrente dei protocolli da visualizzare nelle varie view dei protocolli
     */
    void changeCurrentProtocolsType(romeo::model::protocols::ProtocolType type);

signals:

public slots:

private slots:
    /*!
     * \brief Slot pubblico che visualizza una nuova finestra di dialogo contenente un NewProtocolDialog.
     */
    void viewNewProtocolDialog();

    /*!
     * \brief Slot pubblico che visualizza una nuova finestra di dialogo contenente un AssociateProtocolDialog.
     */
    void viewAssociateProtocolDialog();

    /*!
     * \brief Controlla se il nome del protocollo passato in input è già impegnato da un protocollo e in caso si preoccupa di
     * di far visualizzare un messaggio di errore sul wizard di creazione di un protocollo
     */
    void checkProtocolName(QString protocolName);

    /*!
     * \brief Slot connesso con il segnale createProtocol della classe ProtocolDialog, crea un nuovo protocollo con i parametri in input
     * \param protocolName Nome del protocollo da inserire.
     * \param desc Descrizione del protocollo.
     * \param test Parametro booleano che indica se il protocollo è di test.
     * \param features Lista delle feature che il protocollo deve eseguire.
     * \param algorithm L'algoritmo di clustering associato al protocollo.
     * \param type Il tipo di protocollo che si vuole creare.
     * \param windowSize Dimensione della finestra su cui eseguire il protocollo.
     * \param distanceGLCM Distanza dalla GLCM impostata per il protocollo.
     * \param nClusters Numero di cluster dell'algoritmo di clustering.
     * \param frameInit Indice del frame da cui iniziare le analisi (incluso).
     * \param frameEnd Indice del frame in cui finire le analisi (incluso).
     */
    void addProtocol(QString protocolName,QString desc,bool test,QList<QString>features,QString algorithm,romeo::model::protocols::ProtocolType type,int windowSize,int distanceGLCM,int nClusters,int frameInit, int frameEnd, QList<QString> parametersValue);

    /*!
     * \brief Slot che si preoccura di associare al dataset corrente il protocollo con nome dato in input
     */
    void associateProtocol(QString protocolName);

    /*!
     * \brief Slot che elimina dalla lista dei protocolli il nome del protocollo dato in input e rimuove tutte le associazioni a tale protocollo nei vari dataset
     */
    void deleteProtocol(QString protocolName);

    /*!
     * \brief Slot che elimina dal dataset corrente l'associazione con il protocollo dato in input
     */
    void removeProtocolAssociation(QString protocolName);



    /*!
     * \brief Slot che apre sul dialogo per la visualizzazione del protocollo, il protocollo con nome dato in input
     */
    void openProtocol(QString protocolName);


    void modifyProtocol(QString oldProtocolName,QString protocolName,QString desc,bool test,QList<QString>features,QString algorithm,romeo::model::protocols::ProtocolType type,int windowSize,int distanceGLCM,int nClusters, int frameInit, int frameEnd, QList<QString> parametersValue);


private:

    /*!
     * \brief Metodo che collega i segnali emessi dalle varie view agli slot presenti nel controller
     */
    void connectViewsSignals();

    /*!
     * \brief Campo dati statico che contiene il riferimento all'unica istanza del ProtocolsController
     */
    static ProtocolsController* instance;

    /*!
     * \brief Riferimento al Widget che mostra la lista dei protocolli del programma
     */
    romeo::view::mainWindow::ProtocolsExplorer* protocolsExplorer;

    /*!
     * \brief Riferimento al Widget che mostra il panello con la lista dei protocolli associati al dataset corrente
     */
    romeo::view::mainWindow::ProtocolsPanel* protocolsPanel;

    /*!
     * \brief Riferimento al dialogo per l'aggiunta o la modifica di un protocollo
     */
    romeo::view::dialogs::ProtocolDialog* protocolDialog;


    /*!
     * \brief Riferimento al widget che mostra la lista dei protocolli che si possono associare al dataset corrente.
     */
    romeo::view::dialogs::AssociateProtocolDialog* associateProtocolDialog;

    /*!
     * \brief Puntatore all'unica istanza di AlgorithmsList.
     */
    romeo::model::protocols::algorithms::AlgorithmsList* algorithmsList;
    /*!
     * \brief Puntatore all'unica istanza di FeaturesList.
     */
    romeo::model::protocols::features::FeaturesList* featuresList;
    /*!
     * \brief Puntatore all'unica istanza di ProtocolsList.
     */
    romeo::model::protocols::ProtocolsList* protocolsList;

    romeo::view::mainWindow::MainWindow* mainWindow;

};

}
}
#endif // PROTOCOLSCONTROLLER_H
