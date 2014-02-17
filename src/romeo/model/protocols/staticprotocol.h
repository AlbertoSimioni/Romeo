/**
* \file staticprotocol.h
* \author Matteo Pozza
* \date 2014-02-07
**
* \brief Header della classe StaticProtocol del package romeo::model::protocols
*/

#ifndef STATICPROTOCOL_H
#define STATICPROTOCOL_H
#include "abstractprotocol.h"

namespace romeo {
namespace model {
namespace protocols{

class StaticProtocol : public AbstractProtocol
{
public:
    StaticProtocol();
};
}}}
#endif // STATICPROTOCOL_H
