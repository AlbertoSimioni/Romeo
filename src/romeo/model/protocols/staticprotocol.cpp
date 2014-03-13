/**
* \file staticprotocol.cpp
* \author Matteo Pozza
* \date 2014-02-07
**
* \brief Header della classe StaticProtocol del package romeo::model::protocols
*/

#include "staticprotocol.h"
#include <QMessageBox>
#include <QDebug>
#include <QThread>

using namespace romeo::model::protocols;
using namespace romeo::model::imageIO;
using namespace romeo::model;

StaticProtocol::StaticProtocol(QString nomeP, QString desc, algorithms::AbstractAlgorithm* alg, int clusterNum, QList<QString> algParameters, QList<features::AbstractFeature*> feat, bool testProtocol, int window, int distance):
    AbstractProtocol(nomeP,desc,alg, clusterNum, algParameters, feat,testProtocol), windowSize(window), distanceToGLCM(distance)
{

}

void StaticProtocol::execute(romeo::model::datasets::AbstractSubject *subject,QString path,bool saveFeatures,QString outputFormat)
{
    setStopAnalysis(false);
    InputFormat dimensions = subject->getType();
    if(dimensions == TYPE2D)
        templateExecute<2>(subject,path,saveFeatures,outputFormat);
    else
        templateExecute<3>(subject,path,saveFeatures,outputFormat);
}


ProtocolType StaticProtocol::getType(){
    return STATIC;
}
int StaticProtocol::getWindowSize() const
{
    return windowSize;
}

void StaticProtocol::setWindowSize(int value)
{
    windowSize = value;
}

int StaticProtocol::getDistanceToGlcm() const
{
    return distanceToGLCM;
}

void StaticProtocol::setDistanceToGlcm(int value)
{
    distanceToGLCM = value;
}

double** StaticProtocol::transform(double** result,const int nrows,const int ncolumns) {
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


int* StaticProtocol::normalize(double* array,int length) {
    // normalizza un array di double in una scala da 0 a 255
    // l'array è con valori >=0
    double max = array[0];
    double min = array[0];
    int maxIndex = 0;
    int minIndex = 0;
    for(int i=1;i<length;i++) {
        if(max<array[i]) {
            max=array[i];
            maxIndex=i;
        }
        if(min>array[i]) {
            min=array[i];
            minIndex=i;
        }
    }
    int* result = new int[length];
    if(max!=255.0 || min!=0.0) {
        if(min==max) {
            // tutti gli elementi sono uguali
            for(int i=0;i<length;i++)
                result[i] = 255;
        }
        else {
            // bisogna normalizzare
            for(int i=0;i<length;i++) {
                result[i] = roundToInt(((array[i]-min)*255)/(max-min));
            }
        }
    }
    else {
        // array regolare con min=0 e max=255
        for(int i=0;i<length;i++)
            result[i] = roundToInt(array[i]);
    }
    return result;
}

int StaticProtocol::roundToInt(double num) {
    // metodo per arrotondare ad intero un double
    return static_cast<int>(num + 0.5);
}
