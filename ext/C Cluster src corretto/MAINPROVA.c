#include <iostream>
#include "hierarchical.c"
#include "fcm.cpp"
// info su array e puntatori qua: http://stackoverflow.com/questions/8767166/passing-2d-array-to-function

using namespace std;

  int main() {
	 const int nclusters = 10;
	 const int nrows = 3000;
	 const int ncolumns = 10;
	 int i,j;

	 double** data = new double*[nrows];
	 for(i = 0; i <nrows; i++)
    	data[i] = new double[ncolumns];	
	//valori da analizzare pseudo random con i+j	
	 for(i=0;i<nrows;i++) {
		 for(j=0;j<ncolumns;j++) {
			 data[i][j] = i+j;
		 }
	 }


	 int** mask = new int*[nrows];
	 for(i = 0; i <nrows; i++)
    	mask[i] = new int[ncolumns];	
	//Setto la maschera tutta a 1 così li analizza tutti	 
	for(i=0;i<nrows;i++) {
		 for(j=0;j<ncolumns;j++) {
			 mask[i][j] = 1;
		 }
	  }
	//vettore dei pesi tutti a 1
	 double* weight = new double[nrows];
	 for(j=0;j<nrows;j++) {
		 weight[j] = 1.0;
	 }

	 int* clusterid = new int[nrows];
	 for(j=0;j<nrows;j++) {
		 clusterid[j] = 0;
	 }

	 double error;
	 int ifound ;

	cout<< "Kmeans\n";

	cout<< "inizio\n";
	// Finalmente chiamo l'algoritmo
	kcluster (nclusters, nrows, ncolumns, data, mask, weight, 0, 0, 'a', 'e', clusterid, &error, &ifound);
	//Stampa il risulato	 
	for(i=0;i<nrows;i++) {
		if(i%60 == 0){cout<<"\n";}
		cout << clusterid[i];
	 }
	//flag
	cout<<"\nSoluzione buona ->"<< ifound <<"\n";

	//non ho voglia di deallocare la memoria -> memory leak!!

	cout<< "Hierarchical\n";

	cout<< "inizio\n";

	hierarchicalAlgorithm(nclusters, nrows, ncolumns, data, mask, weight, 'e', 0, 'a', clusterid);

	//Stampa il risulato	 
	for(i=0;i<nrows;i++) {
		if(i%60 == 0){cout<<"\n";}
		cout << clusterid[i];
	 }
	//flag
	cout<<"\nSoluzione buona ->"<< ifound <<"\n";

	cout<< "FuzzyCMeans\n";

	cout<< "inizio\n";

	fcm(nclusters, nrows, ncolumns, data, 0.005, 2, clusterid);

	//Stampa il risulato	 
	for(i=0;i<nrows;i++) {
		if(i%60 == 0){cout<<"\n";}
		cout << clusterid[i];
	 }

	cout << "\n";
 }
