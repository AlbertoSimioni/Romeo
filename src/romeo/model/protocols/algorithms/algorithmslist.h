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
#include<QObject>
namespace romeo {
namespace model {
namespace protocols{
namespace algorithms{

/**
 * \brief La classe AlgorithmsList da completare
 *
 * Descrizione dettagliata
 */

class AlgorithmsList: public QObject
{
    Q_OBJECT
public:
    explicit AlgorithmsList(QObject *parent = 0);
};
}}}}
#endif // ALGORITHMSLIST_H
