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

/*!
 * \brief La classe StaticProtocol rappresenta i protocolli che eseguono su immagini statiche.
 * *
 * La classe eredita da AbstractProtocol e implementa il metodo virtuale puro execute(AbstractSubject*) con cui esegue un protocollo sul subject, che deve essere un immagine di tipo statico.
 */
class StaticProtocol : public AbstractProtocol
{
public:
    StaticProtocol(QString nomeP, QString desc, algorithms::AbstractAlgorithm* alg, QList<features::AbstractFeature*> feat,bool testProtocol, int window=3, int distance=1);
    /*!
     * \brief Override del metodo execute della classe astratta AbstractProtocol
     * \param Il soggetto utilizzato per eseguire l'analisi, deve contenere un immagine di tipo statico
     */
    virtual void execute(datasets::AbstractSubject *subject);

    virtual ProtocolType getType();
    int getDistanceToGLCM() const;
    void setDistanceToGLCM(int value);
    int getWindowSize() const;
    void setWindowSize(int value);
private:
    int distanceToGLCM;
    int windowSize;
};
}}}
#endif // STATICPROTOCOL_H
