#include <math.h>
#include <stdlib.h>

double get_norm(int i, int j,const int &ncolumns,double** data,double** cluster_centre,int* mask) {
    int k;
    double sum = 0.0;
    for (k = 0; k < ncolumns; k++) {
        	sum += pow(data[i][k] - cluster_centre[j][k], 2);
    }
    return sqrt(sum);
}

double get_new_value(int i, int j,const int &nclusters,const int &ncolumns,const double &fuzziness,double** data,double** cluster_centre,int*mask) {
    int k;
    double t, p, sum;
    sum = 0.0;
    p = 2 / (fuzziness - 1);
    for (k = 0; k < nclusters; k++) {
        t = get_norm(i, j,ncolumns,data,cluster_centre,mask) / get_norm(i, k,ncolumns,data,cluster_centre,mask);
        t = pow(t, p);
        sum += t;
    }
    return 1.0 / sum;
}

void calculate_centre_vectors(const int &nclusters,const int &nrows,const int &ncolumns,const double &fuzziness,double** data,double** degree_of_memb,double** cluster_centre,int*mask) {
    int i, j, k;
    double numerator, denominator;
    double** t = new double*[nrows];
    for(i=0;i<nrows;i++)
		if(mask[i]!=0)
    		t[i] = new double[nclusters];
    for (i = 0; i < nrows; i++) {
		if(mask[i]!=0){
        	for (j = 0; j < nclusters; j++) {
            	t[i][j] = pow(degree_of_memb[i][j], fuzziness);
        	}
		}
    }
    for (j = 0; j < nclusters; j++) {
        for (k = 0; k < ncolumns; k++) {
            numerator = 0.0;
            denominator = 0.0;
            for (i = 0; i < nrows; i++) {
				if(mask[i]!=0){
                	numerator += t[i][j] * data[i][k];
                	denominator += t[i][j];
				}
            }
            cluster_centre[j][k] = numerator / denominator;
        }
    } 
	// delete t
	for(i=0;i<nrows;i++)
		delete[] t[i];
    delete[] t;
}

double update_degree_of_membership(const int &nclusters,const int &nrows,const int &ncolumns,const double &fuzziness,double** data,double** degree_of_memb,double** cluster_centre,int*mask) {
    int i, j;
    double new_uij;
    double max_diff = 0.0, diff;
    for (j = 0; j < nclusters; j++) {
        for (i = 0; i < nrows; i++) {
			if(mask[i]!=0){
            new_uij = get_new_value(i, j,nclusters,ncolumns,fuzziness,data,cluster_centre,mask);
            diff = new_uij - degree_of_memb[i][j];
            if (diff > max_diff)
                max_diff = diff;
            degree_of_memb[i][j] = new_uij;
			}
        }
    }
    return max_diff;
}

void fcm(const int nclusters,const int nrows,const int ncolumns,double** data,double epsilon,double fuzziness,int clusterid[],int*mask) {
    double max_diff;
    int i,j,r;
    double s,rval;
    // creation of degree_of_memb
    double** degree_of_memb = new double*[nrows];
    for(int k=0;k<nrows;k++)
    	degree_of_memb[k]=new double[nclusters];
    // inizialization of degree_of_memb
    for (i = 0; i < nrows; i++) {
        s = 0.0;
        r = 100;
        for (j = 1; j < nclusters; j++) {
            rval = rand() % (r + 1);
            r -= rval;
            degree_of_memb[i][j] = rval / 100.0;
            s += degree_of_memb[i][j];
        }
        degree_of_memb[i][0] = 1.0 - s;
    }
    // creation of cluster_centre
	double** cluster_centre = new double*[nclusters];
    for(int k=0;k<nclusters;k++)
    	cluster_centre[k]=new double[ncolumns];
    // real algorithm
    do {
        calculate_centre_vectors(nclusters,nrows,ncolumns,fuzziness,data,degree_of_memb,cluster_centre,mask);
        max_diff = update_degree_of_membership(nclusters,nrows,ncolumns,fuzziness,data,degree_of_memb,cluster_centre,mask);
    } while (max_diff > epsilon);
    // delete cluster_centre
    for(i=0;i<nclusters;i++)
    	delete[] cluster_centre[i];
    delete[] cluster_centre;
    // compute clusterid
    for(i=0;i<nrows;i++) {
		if(mask[i]!= 0){
		double max = -1;
		int index = 0;
		for(j=0;j<nclusters;j++) {
			if(degree_of_memb[i][j]>max) {
				max = degree_of_memb[i][j];
				index = j;
			}
		}
		clusterid[i] = index;
	}
	}
	// delete degree_of_memb
    for(i=0;i<nrows;i++)
    	delete[] degree_of_memb[i];
    delete[] degree_of_memb;
}
