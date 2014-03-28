/**
* \file abstractprotocol.cpp
* \author Matteo Pozza
* \date 2014-02-17
**
* \brief Header della classe AbstractProtocol del package romeo::model::protocols
*/

#include "abstractprotocol.h"

#include <QStringList>
using namespace romeo::model::protocols;
using namespace romeo::model::protocols::algorithms;
using namespace romeo::model::protocols::features;


AbstractProtocol::AbstractProtocol(QString nomeP, QString desc, AbstractAlgorithm *alg, int clusterNum, QList<QString> algParameters, QList<AbstractFeature *> &feat,bool testProtocol):
    name(nomeP),description(desc),algorithm(alg), nClusters(clusterNum), algorithmParameters(algParameters), features(feat),test(testProtocol),stopAnalysis(false)
{
}

QString AbstractProtocol::getName() const
{
    return name;
}

QString AbstractProtocol::getDescription() const
{
    return description;
}


bool AbstractProtocol::getTest() const
{
    return test;
}

QList<AbstractFeature *> AbstractProtocol::getFeatures() const
{
    return features;
}

AbstractAlgorithm* AbstractProtocol::getAlgorithm() const
{
    return algorithm;
}

QStringList AbstractProtocol::getFeaturesName() const
{
    QStringList featureNames;
    for(int i=0; i< features.length(); ++i)
    {
        featureNames << features.at(i)->getName();
    }
    return featureNames;
}

QString AbstractProtocol::getAlgorithmName() const
{
    QString algorithmName;
    if(algorithm) algorithmName = algorithm->getName();
    return algorithmName;
}
int AbstractProtocol::getNClusters() const
{
    return nClusters;
}

void AbstractProtocol::setNClusters(int value)
{
    nClusters = value;
}
QList<QString> AbstractProtocol::getAlgorithmParameters() const
{
    return algorithmParameters;
}

void AbstractProtocol::setAlgorithmParameters(const QList<QString> &value)
{
    algorithmParameters = value;
}
bool AbstractProtocol::getStopAnalysis() const
{
    return stopAnalysis;
}

void AbstractProtocol::setStopAnalysis(bool value)
{
    stopAnalysis = value;
}

double** AbstractProtocol::transform(double** result,const int nrows,const int ncolumns) {
    // input: result[ncolumns][nrows]
    // output: result[nrows][ncolumns]
    double** transf = new double*[nrows];
    for(int i=0;i<nrows;i++)
        transf[i]=new double[ncolumns];
    // copy
    for(int i=0;i<ncolumns;i++) {
        for(int j=0;j<nrows;j++)
            transf[j][i]=result[i][j];
    }
    // remove result
    for(int i=0;i<ncolumns;i++)
        delete[] result[i];
    delete[] result;

    // return transformed
    return transf;
}

void AbstractProtocol::findMinMax(double first,double second,double third,double* max,double* min) {
    if(first > second) {
        // first > second
        if(second > third) {
            // first > second > third
            *max = first;
            *min = third;
        }
        else {
            // first > second && third > second
            if(first > third) {
                // first > third > second
                *max = first;
                *min = second;
            }
            else {
                // third > first > second
                *max = third;
                *min = second;
            }
        }
    }
    else {
        // second > first
        if(first > third) {
            // second > first > third
            *max = second;
            *min = third;
        }
        else {
            // second > first && third > first
            if(second > third) {
                // second > third > first
                *max = second;
                *min = first;
            }
            else {
                // third > second > first
                *max = third;
                *min = first;
            }
        }
    }
}

void AbstractProtocol::normalize(double* redValues,double* greenValues,double* blueValues,int* finalRed,int* finalGreen,int* finalBlue,int* mask,int length) {
    // normalizza gli array di double in una scala da 0 a 255
    // i valori possono essere anche negativi
    double max = redValues[0];
    double min = redValues[0];
    for(int i=0;i<length;i++) {
        if(mask[i]>0) {
            double iterMax = 0.0;
            double iterMin = 0.0;
            findMinMax(redValues[i],greenValues[i],blueValues[i],&iterMax,&iterMin);
            if(iterMax>max)
                max = iterMax;
            if(iterMin<min)
                min = iterMin;
        }
    }
    if(max!=255.0 || min!=0.0) {
        if(min==max) {
            // tutti gli elementi sono uguali
            for(int i=0;i<length;i++) {
                finalRed[i] = 255;
                finalGreen[i] = 255;
                finalBlue[i] = 255;
            }
        }
        else {
            // bisogna normalizzare
            for(int i=0;i<length;i++) {
                if(mask[i]>0) {
                    finalRed[i] = roundToInt(((redValues[i]-min)*255)/(max-min));
                    finalGreen[i] = roundToInt(((greenValues[i]-min)*255)/(max-min));
                    finalBlue[i] = roundToInt(((blueValues[i]-min)*255)/(max-min));
                }
                else {
                    finalRed[i] = 0;
                    finalGreen[i] = 0;
                    finalBlue[i] = 0;
                }
            }
        }
    }
    else {
        // array regolare con min=0 e max=255
        for(int i=0;i<length;i++) {
            if(mask[i]>0) {
                finalRed[i] = roundToInt(redValues[i]);
                finalGreen[i] = roundToInt(greenValues[i]);
                finalBlue[i] = roundToInt(blueValues[i]);
            }
            else {
                finalRed[i] = 0;
                finalGreen[i] = 0;
                finalBlue[i] = 0;
            }
        }
    }
}

int AbstractProtocol::roundToInt(double num) {
    // metodo per arrotondare ad intero un double
    return static_cast<int>(num + 0.5);
}
