/**
* \file modelcore.h
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


/**
 * \brief La classe AbstractFeature da completare
 *
 * Descrizione dettagliata
 */
class AbstractFeature
{
    /*!
     * \brief dynamicLibraryPath
     */
    QString dynamicLibraryPath;
    QString dynamicFunctionName;
    QString name;
    QString description;
public:
    AbstractFeature();

    /*!
     * \brief Restituisce
     */
    QString getDynamicLibraryPath() const;
};

}}}}

#endif // ABSTRACTFEATURE_H
