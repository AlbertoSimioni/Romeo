/**
* \file abstractfeature.h
* \author Alberto Cavallarin
* \date 17-02-2014
**
* \brief  Header della classe AbstractFeature del package romeo::model::protocols::features
*/

#ifndef ABSTRACTFEATURE_H
#define ABSTRACTFEATURE_H
#include<QString>
namespace romeo {
namespace model {
namespace protocols{
namespace features{

/*!
 * \brief Tipo enumerazione che identifica i vari tipi di feature extractor.
 */
enum FeatureType{FIRSTORDER,SECONDORDER,DYNAMIC};

/**
 * \brief Classe astratta che rappresenta un feature extractor utilizzato per ricavare delle particolari caratteristiche sulle immagini da analizzare. La classe è stata progettata con l'intenzione di rappresentare un feature extractor come un oggetto (istanza di una classe) e non solamente come un metodo o una funzione.
 *
 * Contiene le informazioni comuni e necessarie a tutti i tipi di feature extractor. Inoltre mette a disposizione i metodi per la modifica e il reperimento di tali informazioni. Dichiara i metodi relativi all'estrazione della feature, tutte le sottoclassi dovranno rispettare la firma definita.
 */
class AbstractFeature
{
    /*!
     * \brief  Stringa contenente il percorso nel file system con la libreria dinamica contenete il codice del feature extractor.
     */
    QString dynamicLibraryPath;
    /*!
     * \brief Stringa contente il nome della funzione all'interno della libreria dinamica.
     */

    QString dynamicFunctionName;
    /*!
     * \brief Nome della feature.
     */
    QString name;
    /*!
     * \brief Descrizione della feature.
     */
    QString description;
    /*!
     * \brief Indica il tipo della feature tra quelli disponibili in FeatureType.
     */
    FeatureType type;
public:
    /*!
     * \brief Costruisce una nuova feature con i parametri indicati.
     * \param featureName Nome della feature da costruire.
     * \param dylp Percorso al file contenente la libreria dinamica della feature.
     * \param dyfn Nome della funzione da utilizzare per eseguire la feature.
     * \param description Descrizione della feature.
     */
    AbstractFeature(QString featureName,QString dylp,QString dyfn,QString description = QString());

    virtual ~AbstractFeature();
    /*!
     * \brief Restituisce il percorso alla libreria dinamica contente il codice del feature extractor.
     */
    QString getDynamicLibraryPath() const; //forse non necessario
    /*!
     * \brief Restituisce il nome della feature.
     */
    QString getName() const;
    /*!
     * \brief Restituisce la descrizione della feature.
     */
    QString getDescription() const;
    /*!
     * \brief Metodo astratto che restituisce il tipo della feature, sotto forma di stringa.
     */
    virtual FeatureType getType()= 0;
    /*!
     * \brief Ritorna il nome della funzione da chiamare nella libreria dinamica.
     */
    QString getDynamicFunctionName() const;
};

}}}}

#endif // ABSTRACTFEATURE_H
