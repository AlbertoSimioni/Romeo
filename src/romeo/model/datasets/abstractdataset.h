/**
* \file abstractdataset.h
* \author Matteo Pozza
* \date 2014-02-17
**
* \brief Header della classe AbstractDataset del package romeo::model::datasets
*/

#include "result.h"

#include <QHash>
#include <QString>

#include <src/romeo/model/protocols/abstractprotocol.h>
#include "src/romeo/model/inputformats.h"
#include <src/romeo/model/protocols/abstractprotocol.h>

#include <src/romeo/model/protocols/abstractprotocol.h>


#ifndef ABSTRACTDATASET_H
#define ABSTRACTDATASET_H
namespace romeo {
namespace model {
namespace datasets{

/**
 * \brief La classe AbstractDataset da completare
 *
 * Descrizione dettagliata
 */

class AbstractDataset: public QObject
{
    Q_OBJECT
public:
    AbstractDataset();
    /*!
     * \brief Costruisce un nuovo dataset con il nome indicato
     * \param name Nome con cui costruire in nuovo dataset
     */
    AbstractDataset(QString& name);
    /*!
     * \brief Metodo per la creazione di un nuovo subject che prende in input le informazioni necessarie alla creazione e richiama il metodo virtuale makeSubject() che viene ridefinito dalle sottoclassi e permette di creare i vari tipi di subjects.
     * \param n Nome del subject da creare e aggiungere al dataset
     * \param fileSubject Percorso del filesystem al file immagine del subject
     * \param mask Percorso alla mask del subject
     */
    void createNewSubject(QString& name, QString& fileSubject, QString& mask);
    /*!
     * \brief Metodo virtuale puro che deve essere ridefinito dalle sottoclassi in base al tipo di subject che si vuole costruire. Il metodo è chiamato da createNewSubject e costruisce un nuovo subject dello stesso tipo del tipo del dataset che ne ha richiesto la costruzione (2D per i dataset 2D, 3D per quelli 3D ecc..)
     * \param n Nome del subject da creare
     * \param fileSubject Percorso all'immagine associata al subject
     * \param mask Percorso alla maschera associata al subject
     * \return Ritorna un puntatore al nuovo subject appena creato
     */
    virtual AbstractSubject* makeSubject(QString& n, QString& fileSubject, QString& mask) = 0;
    /*!
     * \brief Associa un nuovo protocollo al dataset. Se il protocollo appartiene già al dataset, non viene modificato nulla e viene ritornato il valore false, altrimenti il protocollo viene aggiunto al dataset e viene ritornato true
     * \param protocol Il protocollo da aggiungere al dataset
     */
    void associateProtocol(protocols::AbstractProtocol* protocol);
    /*!
     * \brief Ritorna il nome del dataset
     */
    QString getName() const;
    /*!
     * \brief Modifica il nome del dataset
     */
    void setName(QString &value);
    /*!
     * \brief Ritorna i subject collegati al dataset sotto forma di lista di QString
     */
    QList<AbstractSubject*> getSubjectList()const;

    /*!
     * \brief Se è presente un protocollo con nome uguale a quello in input, lo rimuove dalla lista dei protocolli associati
     */
    void removeProtocolAssociation(QString protocolName);
    /*!
     * \brief Ritorna la lista di protocolli associati al dataset
     */
    QList<protocols::AbstractProtocol*> getAssociatedProtocolsList();

    /*!
     * \brief Ritorna il tipo del dataset
     */
    virtual romeo::model::InputFormat getType() = 0;
    /*!
     * \brief Ritorna il tipo di protocolli che è possibile associare al dataset
     */
    virtual romeo::model::protocols::ProtocolType getProtocolsType() = 0;



    bool execute(protocols::AbstractProtocol* alg, QList<AbstractSubject*> selectedSubjects);
    QStringList getProtocolResults(const QString& protocol) const;
    protocols::AbstractProtocol* getProtocol(const QString& protocolName)const;
    QList<protocols::AbstractProtocol*> getProtocolList() const;
    AbstractSubject* getSubject(const QString& subjectName) const;

    void deleteSubject(const QString& subjectName);
signals:
    void addedSubject(QString subjectName, QString dataPath, QString maskPath);
    void removedSubject(QString subjectName);
    void protocolsModified();
    void newResults();

private:
    /*!
     * \brief Nome del dataset.
     */
    QString name;
    /*!
     * \brief Una hashmap che contiene i subject collegati al dataset e i risultati dei protocolli a loro legati.
     */
    QHash<protocols::AbstractProtocol*, QList<Result*> >  protocols;



    /*!
     * \brief Lista dei protocolli che si possono invocare dal dataset.
     */
    QList<AbstractSubject*> subjects;
};
}}}
#endif // ABSTRACTDATASET_H
