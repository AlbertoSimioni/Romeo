/**
* \file modelcore.h
* \author Alberto Cavallarin
* \date 17-02-2014
**
* \brief  Header della classe DynamicFeature del package romeo::model::protocols::features
*/

#ifndef FEATURESLIST_H
#define FEATURESLIST_H

#include <QObject>
#include"abstractfeature.h"

namespace romeo {
namespace model {
namespace protocols{
namespace features{

/**
 * \brief La classe DynamicFeature da completare
 *
 * Descrizione dettagliata
 */


class FeaturesList : public QObject
{
    Q_OBJECT
public:
    explicit FeaturesList(QObject *parent = 0);

signals:

public slots:

};
}}}}
#endif // FEATURESLIST_H
