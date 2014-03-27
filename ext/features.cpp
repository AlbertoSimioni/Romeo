#include "features.h"

    /*FUNZIONE DI CONTROLLO */

double check(double input) {
    if(isnan(input))
        return 0.0;
    else
        return input;
}

    /*FINE FUNZIONE DI CONTROLLO */

	/* FEATURE PRIMO ORDINE */

double feat_p1_mean(double* data,int size,int dimension) {
    int nvol = static_cast<int>(pow(size,dimension));
    double accum = 0.0;
    for(int i=0;i<nvol;i++)
        accum += data[i];
    return check(accum/nvol);
}

double feat_p1_std(double* data,int size,int dimension) {
    int nvol = static_cast<int>(pow(size,dimension));
    double accum = 0.0;
    double mean = feat_p1_mean(data,size,dimension);
    for(int i=0;i<nvol;i++)
        accum += pow(data[i]-mean,2);
    return check(sqrt(accum/nvol));
}

double feat_p1_kurt(double* data,int size,int dimension) {
	int nvol = static_cast<int>(pow(size,dimension));
	double mean = feat_p1_mean(data,size,dimension);
	double std = feat_p1_std(data,size,dimension);
	double accum1 = 0.0;
	for(int i=0;i<nvol;i++)
		accum1 += pow(data[i]-mean,4);
	double accum2 = accum1/nvol;
    return check((accum2/pow(std,4))-3);
}

double feat_p1_skew(double* data,int size,int dimension) {
	int nvol = static_cast<int>(pow(size,dimension));
	double mean = feat_p1_mean(data,size,dimension);
	double std = feat_p1_std(data,size,dimension);
	double accum1 = 0.0;
	for(int i=0;i<nvol;i++)
		accum1 += pow(data[i]-mean,3);
	double accum2 = accum1/nvol;
    return check(accum2/pow(std,3));
}

	/*FINE FEATURE PRIMO ORDINE */
	
	
	/*FEATURE SECONDO ORDINE */
	
double feat_p2_contr(int data[4][4]) {
    double ct = 0;
    for(int i=0;i<4;i++) {
        for(int j=0;j<4;j++) {
            ct += data[i][j]*pow(i-j,2);
        }
    }
    return check(ct);
}

	//*FUNZIONI UTILIZZATE DA feat_p2_corr*//

//PRE: result[] deve essere un array di 4 elementi.
void meanIndexI(int data[4][4],int result[4]) {
	int ct = 0;
	for(int i=0;i<4;i++) {
		for(int j=0;j<4;j++) {
			ct += i*data[i][j];
		}
		result[i] = ct;
		ct = 0;
	}
}

//PRE: result[] deve essere un array di 4 elementi.
void meanIndexJ(int data[4][4],int result[4]) {
	int ct = 0;
	for(int j=0;j<4;j++) {
		for(int i=0;i<4;i++) {
			ct += j*data[i][j];
		}
		result[j] = ct;
		ct = 0;
	}
}

//PRE: result[] e Mi[] devono essere array di 4 elementi.
void stdIndexI(int data[4][4],int meanI[4],double result[4]) {
	unsigned long long ct = 0;
	for(int i=0;i<4;i++) {
		for(int j=0;j<4;j++) {
			ct = ct+(unsigned long long)data[i][j]*(unsigned long long)(i-meanI[i])*(unsigned long long)(i-meanI[i]);
		}
		result[i] = sqrt(ct);
		ct = 0;
	}
}

//PRE: result[] e Mi[] devono essere array di 4 elementi.
void stdIndexJ(int data[4][4],int meanJ[4],double result[4]) {
	unsigned long long ct = 0;
	for(int j=0;j<4;j++) {
		for(int i=0;i<4;i++) {
			ct += (unsigned long long)data[i][j]*(unsigned long long)(j-meanJ[j])*(unsigned long long)(j-meanJ[j]);
		}
		result[j] = sqrt(ct);
		ct = 0;
	}
}

	/*FINE FUNZIONI UTILIZZATE DA feat_p2_corr*/

double feat_p2_corr(int data[4][4]) {
	int meanI[4];
	int meanJ[4];
	double stdI[4];
	double stdJ[4];
	meanIndexI(data,meanI);
	meanIndexJ(data,meanJ);
	stdIndexI(data,meanI,stdI);
	stdIndexJ(data,meanJ,stdJ);
	double ct1 = 0;
	double ct2 = 0;
	for(int i=0;i<4;i++) {
		for(int j=0;j<4;j++) {
			/*Se data[i][j]==0 => stdI[i] e stdJ[j] sono uguali a zero => non incremento ct2*/
			/*Se (i-meanI[i])==0 => stdI[i] è uguale a zero => non incremento ct2*/
			/*Se (j-meanJ[j])==0 => stdJ[j] è uguale a zero => non incremento ct2*/
			ct1 = data[i][j]*(i-meanI[i])*(j-meanJ[j]);
			if(ct1!=0) {
				ct2 += ct1/(stdI[i]*stdJ[j]);
			}
		}
	}
    return check(ct2);
}

double feat_p2_energy(int data[4][4]) {
	double ct = 0;
	for(int i=0;i<4;i++) {
		for(int j=0;j<4;j++) {
			ct += pow(data[i][j],2);
		}
	}
    return check(ct);
}

double feat_p2_entropy(int data[4][4]) {
	double ct = 0;
	for(int i=0;i<4;i++) {
		for(int j=0;j<4;j++) {
			if(data[i][j]!=0)
				ct += data[i][j]*log(data[i][j]); 
		}
	}
    return check(-ct);
}

double feat_p2_homo(int data[4][4]) {
	double ct = 0;
	for(int i=0;i<4;i++) {
		for(int j=0;j<4;j++) {
			ct += data[i][j]*(1/(1+std::abs(i-j)));
		}
	}
    return check(ct);
}

	/*FINE FEATURE SECONDO ORDINE */

    /*INIZIO FEATURE DINAMICHE */

double* clust_par_mean(double** data,const int numberOfPixel,int begin,int end) {
    // begin incluso, end incluso
    double* result =new double[numberOfPixel];
    for(int i=0;i<numberOfPixel;i++) {
        double sum = 0.0;
        for(int j=begin;j<=end;j++)
            sum += data[i][j];
        result[i] = sum/(end-begin+1);
    }
    return result;
}
