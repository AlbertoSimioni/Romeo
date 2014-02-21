/**
* \file datasetslist.h
* \author Matteo Pozza
* \date 2014-02-17
**
* \brief Header della classe DatasetsList del package romeo::model::datasets
*/


#ifndef DATASETSLIST_H
#define DATASETSLIST_H
#include"abstractdataset.h"
namespace romeo {
namespace model {
namespace datasets{

/**
 * \brief La classe DatasetsList da completare
 *
 * Descrizione dettagliata
 */


class DatasetsList
{
public:
    DatasetsList();
signals:
    /*!
     * \brief Segnale che indica una modifica avvenuta sulla lista dei dataset
     */
    void datasetListModified();
};
}}}
#endif // DATASETSLIST_H
