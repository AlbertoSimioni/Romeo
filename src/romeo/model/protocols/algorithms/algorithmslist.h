/**
* \file algorithmslist.h
* \author Alberto Cavallarin
* \date 17-02-2014
**
* \brief  Header della classe AlgorithmsList del package romeo::model::protocols::features
*/

#ifndef ALGORITHMSLIST_H
#define ALGORITHMSLIST_H

#include"abstractalgorithm.h"
#include <QObject>
#include <QList>
namespace romeo {
namespace model {
namespace protocols{
namespace algorithms{

/**
 * \brief La classe contiene la lista degli algoritmi caricati e che si possono utilizzari per operazioni di cluster analysis.
 *
 * Fornisce alle classi utilizzatrici metodi per recuperare gli algoritmi, o per inserirli/rimuoverli dal database.
 */

class AlgorithmsList: public QObject
{
    Q_OBJECT
public:
    /*!
     * \brief Metodo statico che ritorna l'istanza di AlgorithmList, in caso sia la prima volta ad essere invocato
     *  si preoccupa anche di costruire l'istanza.
     */
    static AlgorithmsList* getInstance(QObject *parent=0);
    ~AlgorithmsList();
    /*!
     * \brief Inserisce nella lista degli algoritmi un nuovo algoritmo di clustering con i parametri passati.
     * \param name Nome dell'algoritmo di clustering da inserire
     * \param description Descrizione dell'algoritmo di clustering da inserire
     * \param parameters Parametri dell'algoritmo di clustering da inserire
     */
    void addAlgorithm(QString name, QString description, QList<AbstractAlgorithm::AlgorithmParameter> parameters,QString dylp,QString dyfn);
    /*!
     * \brief Aggiunge alla lista degli algoritmi, l'algoritmo passato come puntatore
     */
    void addAlgorithm(AbstractAlgorithm* alg);
    /*!
     * \brief Restituisce la lista completa degli algoritmi
     */
    QList<AbstractAlgorithm*> getAlgorithmsList();

    /*!
     * \brief Restituisce l'algoritmo con il nome dato in input, se non presente ritorna un puntatore nullo
     */
    AbstractAlgorithm* getAlgorithm(QString name);

signals:
    /*!
     * \brief Segnale che indica una modifica alla lista degli algoritmi
     */
    void algorithmsListModified();
private:
    /*!
     * \brief Costruttore privato, poiché la classe Loader implementa il design pattern singleton
     */
    explicit AlgorithmsList(QObject *parent = 0);
    /*!
     * \brief Lista degli algoritmi caricati nell'applicazione e utilizzabili.
     */
    QList<AbstractAlgorithm*> algorithms;
    /*!
     * \brief Puntatore all'unica istanza di AlgorithmsList
     */
    static AlgorithmsList* instance;
};
}}}}
#endif // ALGORITHMSLIST_H
