/**
* \file abstractprotocol.cpp
* \author Matteo Pozza
* \date 2014-02-17
**
* \brief Header della classe AbstractProtocol del package romeo::model::protocols
*/

#ifdef WIN32
#define WINDOWS
#elif WIN64
#define WINDOWS
#elif _WIN32
#define WINDOWS
#elif _WIN64
#define WINDOWS
#endif

#ifdef APPLE
#define MAC
#elif macintosh
#define MAC
#elif Macintosh
#define MAC
#elif __APPLE__&&__MACH__
#define MAC
#endif

#ifdef __gnu_linux__
#define LINUX
#endif

#include "abstractprotocol.h"

#include <QStringList>
#include <QProcess>
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

int AbstractProtocol::getTotalMemory() const {
    int memoryValue = -1;
    QString system_info;
    #ifdef WINDOWS
    MEMORYSTATUSEX memory_status;
    ZeroMemory(&memory_status, sizeof(MEMORYSTATUSEX));
    memory_status.dwLength = sizeof(MEMORYSTATUSEX);
    if (GlobalMemoryStatusEx(&memory_status)) {
      system_info.append(QString("%1").arg(memory_status.ullTotalPhys / (1024 * 1024)));
    } else {
      system_info.append("-1");
    }
    #endif
    #ifdef LINUX
    QProcess p;
    p.start("awk", QStringList() << "/MemTotal/ { print $2 }" << "/proc/meminfo");
    p.waitForFinished();
    QString memory = p.readAllStandardOutput();
    system_info.append(QString("%1").arg(memory.toLong() / 1024));
    p.close();
    #endif
    #ifdef MAC
    QProcess p;
    p.start("sysctl", QStringList() << "hw.physmem");
    p.waitForFinished();
    system_info = p.readAllStandardOutput();
    p.close();
    system_info = system_info.split(": ").at(1).split("\n").at(0);
    #endif
    memoryValue = system_info.toLong()/(1024*1024);
    return memoryValue;
}

QString AbstractProtocol::getMemoryCategory() const {
    int memory = getTotalMemory();
    if(memory<=2048)
        return "2GB";
    else {
        if(memory<=4096)
            return "4GB";
        else {
            return "UNBOUNDED";
        }
    }
}

bool AbstractProtocol::checkRequestedMemory(int requestedMemory) const {
    QString category = getMemoryCategory();
    if(category=="2GB") {
        if(requestedMemory>limit2GB) {
            QString errorMessage = "You are trying to analyze too much data for your architecture.";
            throw errorMessage;
        }
    }
    else if(category=="4GB") {
        if(requestedMemory>limit4GB) {
            QString errorMessage = "You are trying to analyze too much data for your architecture.";
            throw errorMessage;
        }
    }
    return true;
}
