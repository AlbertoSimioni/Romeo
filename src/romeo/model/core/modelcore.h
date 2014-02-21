/**
* \file modelcore.h
* \author Matteo Pozza
* \date 2014-02-17
**
* \brief Header della classe ModelCore del package romeo::model::core
*/

#include "loader.h"
#include "writer.h"

#include <src/romeo/model/imageIO/handlerio.h>
#include <src/romeo/model/imageIO/handlerio.h>
#include <src/romeo/model/datasets/datasetslist.h>
#include <src/romeo/model/protocols/protocolslist.h>
#include <src/romeo/model/protocols/algorithms/algorithmslist.h>
#include <src/romeo/model/protocols/features/featureslist.h>
#include <QDir>
#include <QHash>
#ifndef MODELCORE_H
#define MODELCORE_H

namespace romeo {
namespace model {
namespace core{
/**
 * \brief La classe ModelCore da completare
 *
 * Descrizione dettagliata
 */
class ModelCore : QObject
{
    Q_OBJECT
public:
    static ModelCore* getInstance(QObject* parent=0);
    bool loadData();
    datasets::DatasetsList *getDatasetsList() const;
    protocols::ProtocolsList *getProtocolsList() const;
    protocols::algorithms::AlgorithmsList *getAlgorithmsList() const;
    protocols::features::FeaturesList *getFeaturesList() const;


private:
    ModelCore(QObject* parent=0);

    static ModelCore* instance;
    QDir databaseFile;
    QHash<QString, QDir> datasetsFiles;


    datasets::DatasetsList* createDatasetList(Loader* loader);
    protocols::ProtocolsList* createProtocolList(Loader* loader);
    protocols::algorithms::AlgorithmsList* createAlgorithmList(Loader* loader);
    protocols::features::FeaturesList* createFeatureList(Loader* loader);

    datasets::DatasetsList* datasetsList;
    protocols::ProtocolsList* protocolsList;
    protocols::algorithms::AlgorithmsList* algorithmsList;
    protocols::features::FeaturesList* featuresList;

    imageIO::HandlerIO io2D;
    imageIO::HandlerIO io3D;

public slots:
    bool saveDatasetsList();
    bool saveProtocolsList();
    bool saveAlgorithmsList();
    bool saveFeaturesList();
};


}}}
#endif // MODELCORE_H
