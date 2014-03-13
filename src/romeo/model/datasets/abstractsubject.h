/**
* \file abstractsubject.h
* \author Matteo Pozza
* \date 2014-02-17
**
* \brief Header della classe AbstractSubject del package romeo::model::datasets
*/

#ifndef ABSTRACTSUBJECT_H
#define ABSTRACTSUBJECT_H
#include<QString>
#include <src/romeo/model/inputformats.h>
namespace romeo {
namespace model {
namespace datasets{

/**
 * \brief Classe che rappresenta un subject su cui sarà possibile effettuare le analisi. La classe memorizza la posizione nel file system del RawData relativo all'immagine da analizzare e all'eventuale mask associata.
 *
 * Contiene le informazioni comuni e necessarie a tutti i tipi di subject, inoltre definisce i metodi per la modifica e il reperimento di tali informazioni.
 */

class AbstractSubject
{
public:
    virtual ~AbstractSubject();
    /*!
     * \brief Costruisce un suovo soggetto con il nome indicato
     ** Utilizza i percorsi indicati per inserire nel subject i file di immagine e subject
     * \param nome Il nome del soggetto creato
     * \param fileSubject Il percorso dell'immagine del subject
     * \param fileMask Il percorso alla maschera da applicare
     */
    AbstractSubject(QString& nome, QString& fileSubject, QString& fileMask);
    /*!
     * \brief Ritorna il percorso all'immagine del subject
     */
    QString getSubject();
    /*!
     * \brief Ritorna il percorso alla maschera del subject
     */
    QString getMask();
    /*!
     * \brief Ritorna il nome del subject per identificarlo all'interno di un dataset
     */
    QString getName() const;
    /*!
     * \brief Ritorna il tipo del subject sotto forma di QString. I tipi possibili sono "2D", "2DT", "3D" e "3DT" e dipendono dal tipo dinamico del subject
     */
    virtual romeo::model::InputFormat getType()=0;

private:
    /*!
     * \brief name Nome del subject
     */
    QString name;
    /*!
     * \brief Percorso all'immagine del subject
     */
    QString subject;
    /*!
     * \brief Percorso alla maschera del subject
     */
    QString mask;
};
}}}
#endif // ABSTRACTSUBJECT_H
