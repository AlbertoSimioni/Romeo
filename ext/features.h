#ifndef FEATURES_H
#define FEATURES_H
#ifdef Q_WS_WIN
#define MY_EXPORT __declspec(dllexport)
#else
#define MY_EXPORT
#endif
#include <cmath>
#include <math.h>

/*FEATURE PRIMO ORDINE*/
extern "C" MY_EXPORT double feat_p1_mean(double*,int,int);
extern "C" MY_EXPORT double feat_p1_std(double*,int,int);
extern "C" MY_EXPORT double feat_p1_kurt(double*,int,int);
extern "C" MY_EXPORT double feat_p1_skew(double*,int,int);
/*FINE FEATURE PRIMO ORDINE*/

/*FEATURE SECONDO ORDINE*/
extern "C" MY_EXPORT double feat_p2_contr (int [4][4]);
void meanIndexI(int data[4][4],int*);
void meanIndexJ(int data[4][4],int*);
void stdIndexI(int data[4][4],int*,double*);
void stdIndexJ(int data[4][4],int*,double*);
extern "C" MY_EXPORT double feat_p2_corr (int data[4][4]);
extern "C" MY_EXPORT double feat_p2_energy(int data[4][4]);
extern "C" MY_EXPORT double feat_p2_entropy(int data[4][4]);
extern "C" MY_EXPORT double feat_p2_homo(int data[4][4]);
/*FINE FEATURE SECONDO ORDINE*/

/*FEATURE DINAMICHE */
extern "C" MY_EXPORT double* clust_par_mean(double** data,const int numberOfPixel,int begin,int end);
double trapz (double*, double*, const int);
extern "C" MY_EXPORT double* clust_par_auc(double**,const int,int,int);
double max(double*,const int);
extern "C" MY_EXPORT double* clust_par_max(double**,const int,int,int);
double min(double*,const int);
extern "C" MY_EXPORT double* clust_par_min(double**,const int,int,int);
double regrCoeff(double*, double*, const int);
extern "C" MY_EXPORT double* clust_par_slope(double**,const int,int,int);
int maxIndex(double*,const int);
extern "C" MY_EXPORT double* clust_par_tpeak(double**,const int,int,int);
//Attenzione, usando questa crasha ROMEO
extern "C" MY_EXPORT double** clust_par_value(double**,const int,int,int);
/*FINE FEATURE DINAMICHE*/

#endif
