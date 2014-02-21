/**
* \file abstractprotocol.h
* \author Matteo Pozza
* \date 2014-02-17
**
* \brief Header della classe AbstractProtocol del package romeo::model::protocols
*/
#ifndef ABSTRACTPROTOCOL_H
#define ABSTRACTPROTOCOL_H
#include<QString>
#include<QList>
#include "algorithms/abstractalgorithm.h"
#include "features/abstractfeature.h"
#include "../datasets/abstractsubject.h"

namespace romeo {
namespace model {
namespace protocols{

/**
 * \brief a classe astratta AbstractProtocol rappresenta un protocollo eseguibile dall'utente
 *
 * La classe contiene metodi per modificare le feature e gli algoritmi di clustering definiti per il protocollo e i metodi per eseguire le funzionalità sui dati passati.
 *
 */
class AbstractProtocol
{
public:
    /*!
     * \brief The TipoProtocollo enum
     */
    enum TipoProtocollo { STATICO, DINAMICO };
    /*!
     * \brief Costruisce un nuovo protocollo con nome e descrizione
     * \param Nome del protocollo
     * \param Descrizione del protocollo
     */
    AbstractProtocol(QString n="", QString d="");
    /*!
     * \brief Costruisce un nuovo protocollo con l''algoritmo e le features indicate
     * \param nomeP Nome del protocollo da costruire
     * \param desc La descrizione del protocollo sotto forma di stringa
     * \param alg Un puntatore all'algoritmo di clustering che il protocollo deve eseguire
     * \param feat Un vettore di puntatori a features che fanno parte del protocollo
     */
    AbstractProtocol(QString nomeP, QString desc, algorithms::AbstractAlgorithm* alg, QList<features::AbstractFeature*>& feat);
    /*!
     * \brief Sostituisce la lista delle feature che il protocollo possiede con quella indicata. Si può modificare la lista delle feature solo se il protocollo corrente è un protocollo di test
     * \param feat Vettore di features che si vogliono inserire nel protocollo
     * \return Ritorna true se la modifica è avvenuta correttamente, false se si è cercati di modificare un protocollo non di test.
     */
    bool setFeatures(QList<features::AbstractFeature*>& feat);
    /*!
     * \brief Inserisce nel protocollo l'algoritmo di clustering che va a eseguire, sostituendo quello attualmente in uso
     * \param alg puntatore all'algoritmo di clustering
     */
    bool setAlgorithm(algorithms::AbstractAlgorithm* alg);
    /*!
     * \brief Modifica lo stato del protocollo da "test" a "ufficiale"
     * \return Ritorna true se la modifica è avvenuta con successo, false nel caso il protocollo fosse già in stato "ufficiale"
     */
    bool setOfficial();
    /*!
     * \brief Esegue il protocollo sul soggetto passato come puntatore
     * \param subject Il soggetto su cui viene eseguito il protocolli
     * \return Ritorna il percorso dove vengono salvati i risultati dell'analisi
     */
    virtual void execute(datasets::AbstractSubject* subject) = 0;
    //virtual void featureExtract() = 0;
private:
    /*!
     * \brief Nome del protocollo
     */
    QString name;
    /*!
     * \brief Breve descrizione del protocollo e delle sue funzionalità
     */
    QString description;
    /*!
     * \brief Il campo test a true indica che il protocollo è di test, a false significa che il protocollo è ufficiale
     */
    bool test;
    /*!
     * \brief Puntatore all'algoritmo di clustering definito per il protocollo
     */
    algorithms::AbstractAlgorithm* algorithm;
    /*!
     * \brief Vettore di puntatori alle features definite per il protocollo
     */
    QList<features::AbstractFeature*> features;
};

}}}
#endif // ABSTRACTPROTOCOL_H
