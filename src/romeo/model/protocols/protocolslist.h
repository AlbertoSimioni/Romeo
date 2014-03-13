/**
* \file protocolslist.h
* \author Matteo Pozza
* \date 2014-02-17
**
* \brief Header della classe ProtocolsList del package romeo::model::protocols
*/


#ifndef PROTOCOLSLIST_H
#define PROTOCOLSLIST_H

#include <QObject>
#include "abstractprotocol.h"

namespace romeo {
namespace model {
namespace protocols{

/**
 * \brief La classe ProtocolsList contiene la lista dei protocolli definiti dall'utente e che sono stati caricati nell'applicazione.
 *
 * La classe si occupa della creazione e della distruzione dei protocolli caricati in memoria. La classe fornisce i metodi per inserire un nuovo protocollo, rimuoverne uno esistente o ottenere un riferimento a un protocollo.
 *
 */
class ProtocolsList : public QObject
{
    Q_OBJECT
public:
    /**
      * \brief Il distruttore della classe ProtocolsList libera dallo heap lo spazio occupato dai protocooli e distrugge la lista.
    */
    ~ProtocolsList();
    /*!
    * \brief Metodo statico che ritorna l'istanza di ProtocolsList, in caso sia la prima volta ad essere invocato
    *  si preoccupa anche di costruire l'istanza.
    */
    static ProtocolsList* getInstance(QObject* parent=0);
    /*!
     * \brief Metodo che si occupa di costruire un nuovo protocollo con i parametri passati e di aggiungerlo alla lista. Viene costruito un protocollo del tipo dato input. Se il protocollo identificato da protocolName esiste già non viene apportata alcuna modifica alla lista.
     * \param nomeP Nome del protocollo da inserire.
     * \param desc Descrizione testuale del protocollo.
     * \param alg Puntatore all'algoritmo di clustering associato al protocollo.
     * \param clusterNum Impostazione che indica il numero di cluster che l'algoritmo andrà a calcolare.
     * \param algParameters Valori associati ai parametri dell'algoritmo di clustering selezionato.
     * \param feat Lista delle feature che il protocollo deve estrarre.
     * \param test Valore booleano che indica se il protocollo che si va a creare è di test oppure no.
     * \param type Indica il tipo del protocollo che si vuole costruire, che può essere STATIC oppure DYNAMIC.
     * \param window Il valore della finestra di pixel su cui vengono fatti i calcoli relativi alle feature.
     * \param distanceGLCM Parametro necessario per il calcolo della matrice GLCM.
     */
    void addProtocol(QString nomeP, QString desc, algorithms::AbstractAlgorithm* alg, int clusterNum, QList<QString> algParameters, QList<features::AbstractFeature *> feat, bool test, ProtocolType type, int window=3, int distanceGLCM=1);
    /*!
     * \brief Ritorna il riferimento al protocollo con nome uguale al parametro name
     * \param name Nome del protocollo da ritornare.
     * \return Riferimento al protocollo
     */
    AbstractProtocol* getProtocol(QString name);
    /*!
     * \brief Rimuove il protocollo con nome uguale al nome dato in input e libera lo spazio in memoria occupato da tale protocollo.
     */
    void removeProtocol(QString protocolName);
    /*!
     * \brief Ritorna la lista contenente i riferimanti ai protocolli presenti nel programma.
     */
    QList<protocols::AbstractProtocol *> getProtocolsList() const;

signals:
    /*!
     * \brief Segnale che indica che è avvenuta una modifica nella lista dei protocolli come un inserimento di un nuovo protocollo o l'eliminzione di un protocollo dalla lista.
     */
    void protocolsListModified();


private:
    /**
     * \brief ProtocolsList costruisce la lista di protocolli
     */
    explicit ProtocolsList(QObject *parent = 0);
    /*!
     * \brief Il vettore contiene la lista dei protocolli creati dall'utente
     */
    QList<protocols::AbstractProtocol*> protocolsList;
    /*!
     * \brief Campo dati statico che contiene il riferimento all'unica istanza di ProtocolsList
     */
    static ProtocolsList* instance;
};
}}}

#endif // PROTOCOLSLIST_H
