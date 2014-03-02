/**
* \file modelcore.h
* \author Alberto Cavallarin
* \date 17-02-2014
**
* \brief  Header della classe AbstractAlgorithm del package romeo::model::protocols::algorithms
*/
#ifndef ABSTRACTALGORITHM_H
#define ABSTRACTALGORITHM_H
#include <QString>
#include <QList>

namespace romeo {
namespace model {
namespace protocols{
namespace algorithms{


/**
 * \brief La classe AbstractAlgorithm da completare
 *
 * Descrizione dettagliata
 */
class AbstractAlgorithm
{
public:
    enum ParameterType{INT,CHAR,DOUBLE,BOOL};
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




    AbstractAlgorithm();
    explicit AbstractAlgorithm(QString name,QList<AlgorithmParameter>, QString description=QString());
    /*!
     * \brief Tipo enumerazione che definisce i vari tipi che possono avere i parametri definiti dall'utente
     */


    /*!
     * \brief The AlgorithmParameter classe che rappresenta un parametro di un algoritmo di clustering definibile
     * dall'utente
     *
     *  Classe interna ad AbtractAlgorithm che rappresenta un parametro dell'algoritmo di clustering
     *  definibile dall'utente contenente nome, tipo e valore di default del parametro.
     */


private:
    /*!
     * \brief  Contiene tutti i parametri di un algoritmo di clustering che l'utente può modificare
     */
    QList<AlgorithmParameter> parameters; //ricordarsi di delete nel distruttore

    /*!
     * \brief  Nome identificativo dell'algoritmo di clustering
     */
    QString name;

    /*!
     * \brief Contiene la descrizione dell'algoritmo di clustering
     */
    QString description;


public:
    //AbstractAlgorithm(QList<AlgorithmParameter> p, QString n, QString d);
    /*!
     * \brief Metodo che esegue l'algoritmo di clustering s
     * \param data RawData su cui effettuare l'algoritmo di clustering ha dimensioni nrows x ncols
     * \param mask Maschera binaria con dimensione nrows
     * \param nrows Numero di righe degli array data e mask
     * \param ncols Numero di colonne dell'array data
     * \param clusterid Array di dimensione nrows in cui verranno inseriti i risultati delle analisi tramite side-effect.
     * In particolare per ogni elemento dell'array viene inserito il cluster di appartenenza
     * \param parameters Vettore contenente i parametri definibili dall'utente, che variano per ogni algoritmo
     * \return Ritorna true se le analisi sono state eseguite correttamente altrimenti ritorna false
     */
    virtual bool execute(double** data, int* mask, int nrows, int ncols,int* clusterid, QList<QString> parameters) =0 ;

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
