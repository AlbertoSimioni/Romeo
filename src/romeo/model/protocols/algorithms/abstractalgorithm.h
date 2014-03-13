/**
* \file abstractalgorithm.h
* \author Alberto Cavallarin
* \date 17-02-2014
**
* \brief  Header della classe AbstractAlgorithm del package romeo::model::protocols::algorithms
*/

#ifndef ABSTRACTALGORITHM_H
#define ABSTRACTALGORITHM_H
#include <QString>
#include <QList>

//#include "ext/fcm.cpp"
//#include "ext/hierarchical.c"

namespace romeo {
namespace model {
namespace protocols{
namespace algorithms{


/**
 * \brief Classe astratta che rappresenta un algoritmo di clustering utilizzato per ricavare delle particolari caratteristiche sulle immagini da analizzare. La classe è stata progettata con l'intenzione di rappresentare un algoritmo come un oggetto (istanza di una classe) e non solamente come un metodo o una funzione.
 *
 * Contiene le informazioni comuni e necessarie a tutti gli algoritmi di clustering. Inoltre definisce i metodi per la modifica e il reperimento di tali informazioni. Definisce la firma del metodo per l'esecuzione dell'algoritmo di clustering e tutte le sottoclassi dovranno rispettare la firma definita. In particolare, avendo gli algoritmi un numero variabile di parametri, viene passato come parametro aggiuntivo un Vector per inserire un numero arbitrario di parametri aggiuntivi. Era stata inizialmente valutata l'ipotesi di incapsulare i parametri aggiuntivi in una classe dedicata: questa ipotesi è stata scartata in quanto avrebbe costretto l'utente a servirsi di ulteriori classi oltre a quelle già presenti nella libreria standard C++ per definire un proprio algoritmo di clustering. La scelta del vettore per il passaggio dei parametri aggiuntivi permette quindi una maggiore semplicità per gli aspetti riguardanti l’estensibilità del software: nonostante sia meno sicura rispetto al fornire all’utente la capacità di utilizzare parametri tipizzati, l’utilizzo di un vettore di stringhe renderà il software più facilmente estendibile. Qualunque utente interessato ad estendere il programma sarà rimandato ad una lettura accurata della relativa sezione del manuale utente che accompagnerà il software.
 */
class AbstractAlgorithm
{
public:
    /*!
     * \brief Tipo enumerazione che definisce i vari tipi che possono avere i parametri definiti dall'utente.
     */
    enum ParameterType{INT,CHAR,DOUBLE,BOOL};
    /*!
     * \brief The AlgorithmParameter classe che rappresenta un parametro di un algoritmo di clustering definibile
     * dall'utente
     *
     *  Classe interna ad AbtractAlgorithm che rappresenta un parametro dell'algoritmo di clustering
     *  definibile dall'utente contenente nome, tipo e valore di default del parametro.
     */
    class AlgorithmParameter
    {
    public:
        AlgorithmParameter(QString parameterName,ParameterType parType, QString defaultPar);
        /*!
         * \brief Ritorna il nome del parametro
         */
        QString getName() const;
        /*!
         * \brief Ritorna il tipo del parametro
         */
        ParameterType getType() const;
        /*!
         * \brief Ritorna il valore di default del parametro
         */
        QString getDefaultParameter() const;
        /*!
         * \brief Ritorna il tipo del parametro sotto forma di stringa
         */
        QString getTypeString() const;


    private:
        /*!
         * \brief  Rappresenta il nome del parametro dell'algoritmo
         */
        QString name;
        /*!
         * \brief  Rappresenta il tipo del parametro
         */
        ParameterType type;
        /*!
         * \brief  Rappresenta il valore di default del parametro dell'algoritmo sotto forma di stringa
         */
        QString defaultParameter;
    };

    /*!
     * \brief Costruttore della classe AbstractAlgorithm che ne imposta i campi dati ai valori passati in input.
     * \param name Nome dell'algoritmo.
     * \param description Descrizione dell'algoritmo.
     */
    explicit AbstractAlgorithm(QString name,QList<AlgorithmParameter>, QString description=QString());


private:
    /*!
     * \brief  Contiene tutti i parametri di un algoritmo di clustering che l'utente può modificare
     */
    QList<AlgorithmParameter> parameters;

    /*!
     * \brief  Nome identificativo dell'algoritmo di clustering
     */
    QString name;

    /*!
     * \brief Contiene la descrizione dell'algoritmo di clustering
     */
    QString description;


public:
    /*!
     * \brief Metodo che esegue l'algoritmo di clustering.
     * \param data RawData su cui effettuare l'algoritmo di clustering ha dimensioni nrows x ncols
     * \param mask Maschera binaria con dimensione nrows
     * \param nrows Numero di righe degli array data e mask
     * \param ncols Numero di colonne dell'array data
     * \param clusterid Array di dimensione nrows in cui verranno inseriti i risultati delle analisi tramite side-effect.
     * In particolare per ogni elemento dell'array viene inserito il cluster di appartenenza
     * \param parameters Vettore contenente i parametri definibili dall'utente, che variano per ogni algoritmo
     * \return Ritorna true se le analisi sono state eseguite correttamente altrimenti ritorna false
     */
    virtual bool execute(double** data, int* mask, int nrows, int ncols,int* clusterid,int ncluster, QList<QString> parameters) =0 ;

    virtual ~AbstractAlgorithm();

    /*!
     * \brief Metodo che ritorna la descrizione dell'algoritmo.
     * \return
     */
    QString getDescription() const;
    /*!
     * \brief Metodo per modificare la descrizione dell'algoritmo, sostituisce la descrizione presente precedentemente
     * con la descrizione presente nel parametro desc
     * \return
     */
    void setDescription(QString desc);
    /*!
     * \brief Ritorna il nome dell'algoritmo
     */
    QString getName() const;
    /*!
     * \brief Ritorna la lista dei parametri dell'algoritmo
     */
    QList<AlgorithmParameter> getParameters() const;

};

}}}}
#endif // ABSTRACTALGORITHM_H
