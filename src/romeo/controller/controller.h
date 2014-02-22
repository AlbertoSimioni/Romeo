/**
* \file controller.h
* \author Matteo Pozza
* \date 2014-02-17
**
* \brief Header della classe Controller del package romeo::controller
*/


#ifndef CONTROLLER_H
#define CONTROLLER_H

#include<QObject>
#include<src/romeo/view/viewmanager.h>
#include<src/romeo/model/core/modelcore.h>
#include<src/romeo/model/protocols/protocolslist.h>
#include<src/romeo/model/protocols/protocolslist.h>

namespace romeo {
namespace controller{

/**
 * \brief La classe Controller da completare
 *
 * Descrizione dettagliata
 */


class Controller : public QObject
{
        Q_OBJECT
public:
    /*!
     * \brief Metodo statico che ritorna l'istanza del controller, in caso sia la prima volta ad essere invocato
     *  si preoccupa anche di costruire l'istanza.
     */
    static Controller* getInstance(QObject* parent = 0);

public slots:
    void viewNewDatasetDialog();
    void viewNewProtocolDialog();
    void viewNewAlgorithmDialog();
    void viewNewFeatureDialog();
    void viewAlgorithmsListDialog();
    void viewFeaturesListDialog();
    /*!
     * \brief Controlla se il nome del protocollo passato in input è già impegnato e in caso si preoccupa di
     * di far visualizzare un messaggio di errore sul wizard di creazione di un protocollo
     */
    void checkProtocolName(QString protocolName);

private:
    /*!
     * \brief Campo dati statico che contiene il riferimento all'unica istanza del controller
     */
    static Controller* instance;
    /*!
     * \brief Costruttore privato del controller, poiché la classe Controller implementa il design pattern singleton
     */
    Controller(QObject* parent = 0);
    /*!
     * \brief Metodo che collega i segnali emessi dalle varie view agli slot presenti nel controller
     */
    void connectViewsSignals();

    /*!
     * \brief Riferimento alla classe facade della view, essa mette a disposizione i metodi per gestire
     * l'apertura delle finestre di dialogo
     */
    romeo::view::ViewManager* viewManager;

    /*!
     * \brief Riferimento alla lista degli algoritmi
     */
    romeo::model::protocols::algorithms::AlgorithmsList* algorithmList;

    /*!
     * \brief Riferimento alla lista delle feature
     */
    romeo::model::protocols::features::FeaturesList* featureList;

    romeo::model::core::ModelCore* modelCore;
};
}}
#endif // CONTROLLER_H
