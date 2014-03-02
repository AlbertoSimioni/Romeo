/**
* \file modelcore.h
* \author Matteo Pozza
* \date 2014-02-17
**
* \brief  Header della classe Loader del package romeo::model::core
*/

#include <QDir>
#include <QDomNode>
#include <src/romeo/model/protocols/algorithms/algorithmslist.h>
#include <src/romeo/model/protocols/features/featureslist.h>
#include <src/romeo/model/protocols/protocolslist.h>
#ifndef LOADER_H
#define LOADER_H


namespace romeo {
namespace model {
namespace core{

/**
 * \brief La classe Loader da completare
 *
 * Descrizione dettagliata
 */
class Loader: public QObject
{
    Q_OBJECT
public:
    /*!
     * \brief Metodo statico che ritorna l'istanza del Loader, in caso sia la prima volta ad essere invocato
     *  si preoccupa anche di costruire l'istanza.
     */
    static Loader* getInstance(QObject* parent);
    /*!
     * \brief Carica la lista delle features che l'utente ha definito e che può utilizzare.
     * \param algFile Il nome del file da caricare viene stabilito dalla classe che chiama il metodo di load.
     * \param algorithmList La lista degli algoritmi in cui devono essere inserite le informazioni raccolte dal file.
     * \return Ritorna true se il caricamento ha avuto successo.
     */
    bool loadAlgorithms(const QString& algFile, protocols::algorithms::AlgorithmsList *algorithmList);
    /*!
     * \brief Carica la lista delle features che l'utente ha definito e che può utilizzare.
     * \param featFile Il nome del file da caricare viene stabilito dalla classe che chiama il metodo di load.
     * \param featureList La lista delle feature in cui devono essere inserite le informazioni raccolte dal file.
     * \return Ritorna true se il caricamento ha avuto successo.
     */
    bool loadFeatures(const QString &featFile, protocols::features::FeaturesList* featureList);
    /*!
     * \brief Carica la lista dei protocolli che l'utente ha definito e che può utilizzare.
     * \param protocolFile Il nome del file da caricare viene stabilito dalla classe che chiama il metodo di load.
     * \param protocolList La lista degli algoritmi in cui devono essere inserite le informazioni raccolte dal file.
     * \return Ritorna true se il caricamento ha avuto successo.
     */
    bool loadProtocols(const QString& protocolFile, protocols::ProtocolsList* protocolList);
    /*!
     * \brief Carica la lista dei dataset che l'utente ha definito e che può utilizzare. Il caricamento delle informazioni sui dataset veri e propri viene fatto solo quando necessario.
     * \param datasetsFile Il nome del file da caricare viene stabilito dalla classe che chiama il metodo di load.
     * \return Ritorna true se il caricamento ha avuto successo.
     */
    bool loadDatasetsNames(const QString& datasetsFile);
    /*!
     * \brief Carica il dataset contenuto nel file "datasetFile".
     * \param datasetFile Il nome del file da caricare.
     * \return Ritorna true se il caricamento ha avuto successo.
     */
    bool LoadDataset(const QString& datasetFile);
private:
    /*!
     * \brief Costruttore privato, poiché la classe Loader implementa il design pattern singleton
     */
    Loader(QObject *parent=0);
    /*!
     * \brief Campo dati statico che contiene il riferimento all'unica istanza del Loader
     */
    static Loader* instance;
    /*!
     * \brief Funzione che legge sa un nodo xml le informazioni riguardanti una feature e la aggiunge alla lista delle feature.
     */
    static bool parseFeature(protocols::features::FeaturesList* featureList, const QDomNode &node);
    /*!
     * \brief Funzione statica di Loader che carica le informazioni presenti in un nodo xml e aggiunge l'algoritmo corrispondente alla lista degli algoritmi.
     */
    static bool parseAlgorithm(protocols::algorithms::AlgorithmsList* algorithmsList, const QDomNode &node);
    static bool parseProtocol(protocols::ProtocolsList* protocolsList, const QDomNode &node);
    static bool parseParameter(QList<protocols::algorithms::AbstractAlgorithm::AlgorithmParameter>& paramList, const QDomNode& node= QDomNode());
};
}}}

#endif // LOADER_H
